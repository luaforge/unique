/***************************************************************************
 *            png.cpp
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

//#define DONT_INCLUDE_IMAGELIBS // запрещаем автоматически подключать статическую библиотеку
//#include <zlib.h>
//#include <libpng/pngconf.h>
#define PNGAPI
#include"image.hxx"
#include<png.h>

namespace unvis{
  using namespace undata;

#define NUM_SIGN 8

  const int IMPNG::sign=0x474E5089; // ! Байты реверсированы (перевернуты)
  const char IMPNG::className[]="PNG_IMAGE";

  void my_png_read_func(png_structp png_ptr,png_bytep data,png_size_t slength){// функция для чтения
    // данных из виртуального буфера, которой будет пользоваться библиотека PNG. На вход
    // подается указатель на структуру содержащую информацию о библиотеке и число байт, которые
    // нужно прочесть. Необходимые данные запишутся в data.
    STREAM* buffer=(STREAM*)png_get_io_ptr(png_ptr);
    buffer->read((char *)data,slength);
  }
  
# define IMAGE_DEBUG(n) cout<<#n<<endl;

  bool IMAGE::ReadPNG(STREAM& inbuf){// чтение PNG данных из виртуального буфера.
    inbuf.seekg(0,STREAM::beg);			//Сбрасываем буфер
    png_byte sig[NUM_SIGN];
    inbuf.read(sig,sizeof(png_byte)*NUM_SIGN);// проверяем сигнатуру, мы уже проверили,
    //IMAGE_DEBUG(1);
    int gc=inbuf.gcount();
    if(!png_check_sig(sig,NUM_SIGN))return false;// но пусть библиотека сама это сделает на всякий случай
    png_structp png_ptr=png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);// создаем внутреннюю
    //структуру png для работы с файлом
    //IMAGE_DEBUG(2);
    if(!png_ptr)return false;// создаем структуру с информацией о содержимом буффера
    png_infop info_ptr=png_create_info_struct(png_ptr);
    if(!info_ptr){// если где-то при создании произошла ошибка, убиваем внутреннюю структуру
      png_destroy_read_struct(&png_ptr,0,0);
      return false;
    }
    //IMAGE_DEBUG(3);
    png_set_read_fn(png_ptr,(void*)&inbuf,my_png_read_func);// настраиваем библиотеку на наш
    // способ чтения данных
    png_set_sig_bytes(png_ptr,NUM_SIGN);// говорим библиотеке, что мы уже прочли NUM_SIGN байт
    png_read_info(png_ptr,info_ptr);// читаем всю информацию о файле
    // Эта функция возвращает инфу из info_ptr
    int bit_depth=0;  // глубина цвета (одного из каналов, может быть 1, 2, 4, 8, 16)
    int color_type=0; // описывает какие каналы присутствуют:
    // PNG_COLOR_TYPE_GRAY, PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE,
    // PNG_COLOR_TYPE_RGB, PNG_COLOR_TYPE_RGB_ALPHA...
    // последние 3 параметра могут быть нулями и обозначают: тип фильтра, тип компрессии и тип смещения
    png_get_IHDR(png_ptr,info_ptr,(unsigned long*)&width,(unsigned long*)&height,&bit_depth,&color_type,0,0,0);
    // если, вдруг png окажется не того формата что нам нужен, постараемся его сконвертить в нужный нам
    // png формат может содержать 16 бит на канал, но нам нужно только 8, поэтому сужаем канал
    if(bit_depth==16)png_set_strip_16(png_ptr);
    // преобразуем файл если он содержит палитру в нормальный RGB
    if(color_type==PNG_COLOR_TYPE_PALETTE && bit_depth<=8)png_set_palette_to_rgb(png_ptr);
    // если в грэйскейле меньше бит на канал чем 8, то конвертим к нормальному 8-битному
    if(color_type==PNG_COLOR_TYPE_GRAY && bit_depth<8)png_set_gray_1_2_4_to_8(png_ptr);
    // и добавляем полный альфа-канал
    if(png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS))png_set_tRNS_to_alpha(png_ptr);
    // все это можно сделать одной функцией png_set_expand(png_ptr);
    // для преобразования грэйскейл картинки в RGB формат, нуно сделать так:
    if(color_type==PNG_COLOR_TYPE_GRAY || color_type==PNG_COLOR_TYPE_GRAY_ALPHA)
      png_set_gray_to_rgb(png_ptr);
    // для правильного отображения картинки, нужно подобрать гамму в зависимости от настроек
    // монитора, но мы будем проще:
    // 2.2 - хорошо для PC мониторов в освещенной комнате
    // 2.0 - для PC в темной комнате
    // от 1.7 до 1.0 - для систем MacOS
    double gamma=0.0f;
    if(png_get_gAMA(png_ptr,info_ptr,&gamma))png_set_gamma(png_ptr,2.2,gamma);// если есть
    // информация о гамме в файле, то устанавливаем на 2.2
    else png_set_gamma(png_ptr,2.2,0.45455);// иначе ставим дефолтную гамму для
    // образа в 0.45455 (good guess for GIF images on PCs)
    png_read_update_info(png_ptr,info_ptr);// после всех трансформаций, апдейтим информацию
    // опять получаем все размеры и параметры обновленной картинки
    png_get_IHDR(png_ptr,info_ptr,(unsigned long*)&width,(unsigned long*)&height,&bit_depth,&color_type,0,0,0);
    // получаем кол-во каналов на пиксель
    // может быть: 1 (GRAY, PALETTE), 2 (GRAY_ALPHA), 3 (RGB), 4 (RGB_ALPHA или RGB + filler byte)
    channels=png_get_channels(png_ptr,info_ptr);// определяем кол-во байт нужных для того чтобы вместить строку
    png_uint_32 row_bytes=png_get_rowbytes(png_ptr,info_ptr);
    dest();
    init();// теперь, мы можем выделить память чтобы вместить картинку
    png_byte **row_pointers=new png_byte*[height];// выделяем память, для указателей на каждую строку
    // сопоставляем массив указателей на строчки, с выделенными в памяти (res)
    // т.к. изображение перевернутое, то указатели идут снизу вверх
    for(unsigned int i=0;i<height;i++)row_pointers[height-i-1]=pixels+i*row_bytes;
    // читаем картинку
    png_read_image(png_ptr,row_pointers);
    // читаем дополнительную информацию о файле (на самом деле игнорируем ее)
    png_read_end(png_ptr,0);
    // освобождаем память от указателей на строки
    delete[]row_pointers;
    // освобождаем память выделенную для библиотеки libpng
    png_destroy_read_struct(&png_ptr,0,0);
    // записываем информацию о картинке
    switch(color_type){// Устанавливаем формат картинки
    case PNG_COLOR_TYPE_GRAY:	    format=lum;  break;
    case PNG_COLOR_TYPE_GRAY_ALPHA: format=luma; break;
    case PNG_COLOR_TYPE_RGB:	    format=rgb;  break;
    case PNG_COLOR_TYPE_RGB_ALPHA:  format=rgba; break;
    default:			    format=und;  break;
    }
    //Inverse();
    return true;
  };

}
