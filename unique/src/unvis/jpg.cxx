/***************************************************************************
 *            jpg.cpp
 *
 *  Wed Jun 29 17:12:37 2005
 *  Copyright  2005  Fenix
 *  tonder@trktvs.ru
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include<stdio.h>
#ifndef _WIN32
#  include<sys/types.h>
#endif

#include<setjmp.h>
#include<jpeglib.h>

#include"image.hxx"

namespace unvis{

#define ROWS_PREAD 3  // Число строк, читаемых за раз
#define RBUF_SIZE 128 // размер буфера в памяти, куда будем читать информацию

  const int IMJPG::sign=0xE0FFD8FF; // ! Байты реверсированы (перевернуты)
  const char IMJPG::className[]="JPG_IMAGE";
  const int IMAJP::sign=0xE1FFD8FF; // ! Байты реверсированы (перевернуты)
  const char IMAJP::className[]="AJP_IMAGE";

  struct my_error_mgr{         // Наш менеджер обработки ошибок
    struct jpeg_error_mgr pub; // Ссылка на стандартный обработчик ошибок
    jmp_buf setjmp_buffer;     // Для возвращения вызова
  };
  METHODDEF(void) my_error_exit(j_common_ptr cinfo){// Функция обработки ошибок
    my_error_mgr*myerr=(my_error_mgr*)cinfo->err;
    (*cinfo->err->output_message)(cinfo);
    longjmp(myerr->setjmp_buffer,1);// Возвращение вызова setjmp
  }
  struct my_jpeg_source{// Наш менеджер чтения данных
    jpeg_source_mgr pub;    // ссылочка на стандартный менеджер
    STREAM*         file;   // Буфер ввода
    JOCTET*         buffer; // буфер данных
    bool	    sof;    // признак того, что файл только что открыли
  };
  METHODDEF(void) my_init_source(j_decompress_ptr cinfo){// инициализация источника. вызывается 
    //до того, как какая-нибудь информация будет из него прочитана.
    my_jpeg_source*src=(my_jpeg_source*)cinfo->src;
    src->sof=true; // говорим, файл токо что открыт
  }
  METHODDEF(boolean) my_fill_input_buffer(j_decompress_ptr cinfo){// вызывается, когда переменная
    //bytes_in_buffer достигает 0 и возникает необходимость в новой порции информации. 
    //возвращает TRUE, если буфер перезаполнен успешно, и FALSE если произошла ошибка 
    //ввода/вывода.
    my_jpeg_source* src=(my_jpeg_source*)cinfo->src;
    (src->file)->read((char*)src->buffer,RBUF_SIZE*sizeof(JOCTET));
    size_t nbytes=(src->file)->gcount();
    // читаем кусками по RBUF_SIZE байт
    //logout<<nbytes;
    if(nbytes<=0){// если мы ничего не считали
      if(src->sof)return FALSE;	    // пустой файл
      src->buffer[0]=(JOCTET)0xFF;    // если уже читали до этого, то вставляем в буфер инфу 
      src->buffer[1]=(JOCTET)JPEG_EOI;// о конце файла
      nbytes=2;
    }
    src->pub.next_input_byte=src->buffer;	// загоняем инфу в буфер
    src->pub.bytes_in_buffer=nbytes;	// сколько байт прочли
    src->sof=false;			// файл не пустой
    return TRUE;
  }
  METHODDEF(void) my_skip_input_data(j_decompress_ptr cinfo, long num_bytes){// происходит, когда
    // необходимо пропустить num_bytes. в случае опустошения буфера, его необходимо перезагрузить.
    my_jpeg_source*src=(my_jpeg_source*)cinfo->src;
    if(num_bytes<=0)return;// если нужно пропустить 0 байт
    while(num_bytes>(long)src->pub.bytes_in_buffer){// выкидываем инфу из буфера и перегружаем
      num_bytes-=(long)src->pub.bytes_in_buffer;  // его, пока num_bytes не станет меньше 
      my_fill_input_buffer(cinfo);	        // размера буфера
    }
    src->pub.next_input_byte+=(size_t)num_bytes;	// а теперь просто правильно настраиваем 
    src->pub.bytes_in_buffer-=(size_t)num_bytes;	// указатели на оставшуюся часть
  }
  METHODDEF(void) my_term_source(j_decompress_ptr cinfo){// убить ресурс. вызывается функцией 
    //jpeg_finish_decompress когда все данные будут прочтены. у нас ничего сносить не надо.
  }
  // это наш настройщик на нестандартный поток данных
  METHODDEF(void) my_stdio_src(j_decompress_ptr cinfo,STREAM* vbuff){
    my_jpeg_source*src=0;
    if(cinfo->src==0){// смотрим, выделена ли память под JPG декомпрессор менеджер?
      // возможна ситуация, когда происходит одновременное обращение к источнику
      // от нескольких библиотек
      cinfo->src=(struct jpeg_source_mgr*)(*cinfo->mem->alloc_small) 
	((j_common_ptr)cinfo,JPOOL_PERMANENT,sizeof(my_jpeg_source));// выделим память
      // под наш менеджер, и установим на него указатель глобальной структуры библиотеки.
      // так как я использую менеджер памяти библиотеки JPG то позаботится об освобождении
      // она сама. JPOOL_PERMANENT - означает что эта память выделяется на все время работы
      // с библиотекой
      src=(my_jpeg_source*)cinfo->src;
      src->buffer=(JOCTET*)(*cinfo->mem->alloc_small) 
	((j_common_ptr)cinfo,JPOOL_PERMANENT,RBUF_SIZE*sizeof(JOCTET));// выделяю 
      // память для буффера данных, прочитанных из файла
    }
    src=(my_jpeg_source*)cinfo->src;
    src->pub.init_source=my_init_source;// настраиваем обработчики событий на наши функции
    src->pub.fill_input_buffer=my_fill_input_buffer;
    src->pub.skip_input_data=my_skip_input_data;
    src->pub.resync_to_restart=jpeg_resync_to_restart; // используем дефолтный метод
    src->pub.term_source=my_term_source;
    src->file=vbuff;// теперь заполняем поля нашей структуры
    // настраиваем указатели на буферы
    src->pub.bytes_in_buffer=0;	// Ставит fill_input_buffer на первом читаемом
    src->pub.next_input_byte=0;	// Пока буфер незагружен
  }
  bool IMAGE::ReadJPG(STREAM& inbuf){// чтение данных из JPG файла.
    inbuf.seekg(0,STREAM::beg);
    char str[20];
    inbuf.read(str,20);
    inbuf.seekg(0,STREAM::beg);
    jpeg_decompress_struct cinfo;	// Объект для декомпрессии JPG
    my_error_mgr jerr;				// Объект для обработки ошибок
    // Настраиваем обработку ошибок JPEG декомпрессором.
    cinfo.err=jpeg_std_error(&jerr.pub);// устанавливаем дефолтный менеджер обработки ошибок
    jerr.pub.error_exit=my_error_exit;	// присваиваем дефолтную функцию для обработки ошибки
    // Устанавливаем контекст возвращения setjmp на my_error_exit
    if(setjmp(jerr.setjmp_buffer)){// Если произошла ошибка.
      jpeg_destroy_decompress(&cinfo);// Очистим структуру
      return false;
    }
    jpeg_create_decompress(&cinfo);		// инициализируем декомпрессионный объект
    my_stdio_src(&cinfo,&inbuf);		    // указываем источник данных
    jpeg_read_header(&cinfo,TRUE);		// настраиваем заголовок jpeg
    jpeg_start_decompress(&cinfo);		// начинаем декомпрессию
    height=cinfo.output_height;			// Читаем параметри картинки
    width=cinfo.output_width;			// размер
    channels=cinfo.output_components;	// Число байт на пиксель
    switch(cinfo.output_components){	// Формат картинки
    case 1: format=lum;	break;
    case 3: format=rgb;	break;
    default:format=und; break;	
    }
    unsigned int row_stride=cinfo.output_width*cinfo.output_components;// Длина строки
    PixelsInit();// выделяем память для образа
    unsigned int nowRead=0;
    while(nowRead<height){
      JSAMPROW row_pointers[ROWS_PREAD];
      for(int row=0;row<ROWS_PREAD;row++)
	row_pointers[row]=&pixels[(nowRead+row)*row_stride];
      nowRead+=jpeg_read_scanlines(&cinfo,row_pointers,ROWS_PREAD);
    }
    jpeg_finish_decompress(&cinfo);// Завершаем декомпрессию файла
    jpeg_destroy_decompress(&cinfo);// Очищаем объект декомпрессии
    //Inverse();
    return true;
  }
  int FindDataStm(STREAM& istm,int count,void *fdata){
    char chr;
    int i,pos=0;
    int curpos=istm.gcount();
    for(i=0;i<count && !istm.eof();pos++){
      istm.read(&chr,1);
      if(chr==*((char*)fdata+i))i++;else if(i){
	istm.seekg(-1,STREAM::cur);
	i=0;
	pos--;
      }
    }
    istm.seekg(curpos,STREAM::beg);
    if(istm.eof())return -1;
    return i;
  }
  bool IMAGE::ReadAJP(STREAM& inbuf){// Чтение данных из AJP файла
    jpeg_decompress_struct cinfo;// выделяем и инициализируем объект для декомпрессии JPG
    my_error_mgr jerr;
    // Настраиваем обработку ошибок JPEG декомпрессором.
    cinfo.err=jpeg_std_error(&jerr.pub);// устанавливаем дефолтный менеджер обработки ошибок
    jerr.pub.error_exit=my_error_exit;	// присваиваем дефолтную функцию для обработки ошибки
    // Устанавливаем контекст возвращения setjmp на my_error_exit
    if(setjmp(jerr.setjmp_buffer)){// блин, когда-то произошла ошибка. Очистим структуру и закроем файл
      jpeg_destroy_decompress(&cinfo);
      return false;
    }
    // Читаем RGB данные
    jpeg_create_decompress(&cinfo);// инициализируем декомпрессионный объект
    //inbuf->SetData(0,0,8,(void*)ftypes[3]);// Поправим сигнатуру, чтобы не вводить библиотеку
    // в заблуждение нашей, характерной для AJP сигнатурой
    my_stdio_src(&cinfo,&inbuf);// указываем источник данных
    jpeg_read_header(&cinfo,TRUE);// настраиваем заголовок jpeg
    jpeg_start_decompress(&cinfo);// начинаем декомпрессию
    height=cinfo.output_height; // Читаем параметри картинки
    width=cinfo.output_width;	// Размер
    channels=4;//Число байт на пиксель для нашего конечного образа
    format=rgba;//Формат картинки
    unsigned int rgbChan=cinfo.output_components;//Число байт на пиксель для RGB компоненты
    unsigned int row_stride=width*rgbChan;// Длина строки
    unsigned char *rgbPixels=new unsigned char[row_stride*height];
    unsigned int nowRead=0;
    while(nowRead<height){
      JSAMPROW row_pointers[ROWS_PREAD];
      for(unsigned int row=0;row<ROWS_PREAD;row++)
	row_pointers[row]=&rgbPixels[(nowRead+row)*row_stride];
      nowRead+=jpeg_read_scanlines(&cinfo,row_pointers,ROWS_PREAD);
    }
    jpeg_finish_decompress(&cinfo);// Завершаем декомпрессию файла
    jpeg_destroy_decompress(&cinfo);// Очищаем объект декомпрессии
    // Читаем альфа-канал	
    jpeg_create_decompress(&cinfo);// инициализируем декомпрессионный объект
    inbuf.seekg(9,STREAM::beg);// Скачим почти к началу AJP файла
    inbuf.seekg(FindDataStm(inbuf,SIGN_BYTES,(void*)&sign),STREAM::cur);// Нужно поискать где начинается альфа-образ
    my_stdio_src(&cinfo,&inbuf);// указываем источник данных
    jpeg_read_header(&cinfo,TRUE);// настраиваем заголовок jpeg
    jpeg_start_decompress(&cinfo);// начинаем декомпрессию альфа канала
    if(cinfo.output_height<height)height=cinfo.output_height;// Сравниваем размеры
    if(cinfo.output_width<width)width=cinfo.output_width;// Если альфа образ меньше, придется уменьшить картинку
    unsigned int alpChan=cinfo.output_components;
    row_stride=width*alpChan;// Длина строки
    unsigned char *alpPixels=new unsigned char[row_stride*height];// Выделяем память для альфа пикселей
    nowRead=0;
    while(nowRead<height){
      JSAMPROW row_pointers[ROWS_PREAD];
      for(unsigned int row=0;row<ROWS_PREAD;row++)
	row_pointers[row]=&alpPixels[(nowRead+row)*row_stride];
      nowRead+=jpeg_read_scanlines(&cinfo,row_pointers,ROWS_PREAD);
    }
    jpeg_finish_decompress(&cinfo);// Завершаем декомпрессию файла
    jpeg_destroy_decompress(&cinfo);// Очищаем объект декомпрессии
    // Делаем RGBA образ
    PixelsInit();// выделяем память для картинки
    //*loger<<"Channels"<<alpChan<<rgbChan;
    //if(rgbChan==3 && alpChan==1);// Правильная ситуация
    if((rgbChan==1)&&(alpChan==3)){	 // Мы случайно перепутали данные RGB и Alpha местами
      alpChan=1;
      rgbChan=3;
      unsigned char *env=alpPixels;// Чтож, сами поменяем обратно
      alpPixels=rgbPixels;
      rgbPixels=env;
    }
    //*loger<<"Channels"<<alpChan<<rgbChan;
    //if(rgbChan==1 && alpChan==1);// Нам подсунули 2 образа Градации Серого
    //if(rgbChan==3 && alpChan==3);// Если у нас оба образа 3х цветные
    for(unsigned int row=0;row<width*height;row++){// Обработка пикселя	
      *(pixels+row*channels  )=rgbChan==3?*(rgbPixels+row*3  ):*(rgbPixels+row);
      *(pixels+row*channels+1)=rgbChan==3?*(rgbPixels+row*3+1):*(rgbPixels+row);
      *(pixels+row*channels+2)=rgbChan==3?*(rgbPixels+row*3+2):*(rgbPixels+row);
      //*(pixels+row*channels+3)=0xFF;
      *(pixels+row*channels+3)=alpChan==3?(unsigned char)((*(alpPixels+row*3)+// Если в качестве альфы всеже 
							   *(alpPixels+row*3+1)+*(alpPixels+row*3+2))/3):*(alpPixels+row);//идет RGB,найдем пиксель как среднее
    }
    //Inverse();
    delete[]alpPixels;
    delete[]rgbPixels;
    return true;
  }
}
