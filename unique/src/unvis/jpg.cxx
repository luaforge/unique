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

#define ROWS_PREAD 3  // ����� �����, �������� �� ���
#define RBUF_SIZE 128 // ������ ������ � ������, ���� ����� ������ ����������

  const int IMJPG::sign=0xE0FFD8FF; // ! ����� ������������� (�����������)
  const char IMJPG::className[]="JPG_IMAGE";
  const int IMAJP::sign=0xE1FFD8FF; // ! ����� ������������� (�����������)
  const char IMAJP::className[]="AJP_IMAGE";

  struct my_error_mgr{         // ��� �������� ��������� ������
    struct jpeg_error_mgr pub; // ������ �� ����������� ���������� ������
    jmp_buf setjmp_buffer;     // ��� ����������� ������
  };
  METHODDEF(void) my_error_exit(j_common_ptr cinfo){// ������� ��������� ������
    my_error_mgr*myerr=(my_error_mgr*)cinfo->err;
    (*cinfo->err->output_message)(cinfo);
    longjmp(myerr->setjmp_buffer,1);// ����������� ������ setjmp
  }
  struct my_jpeg_source{// ��� �������� ������ ������
    jpeg_source_mgr pub;    // �������� �� ����������� ��������
    STREAM*         file;   // ����� �����
    JOCTET*         buffer; // ����� ������
    bool	    sof;    // ������� ����, ��� ���� ������ ��� �������
  };
  METHODDEF(void) my_init_source(j_decompress_ptr cinfo){// ������������� ���������. ���������� 
    //�� ����, ��� �����-������ ���������� ����� �� ���� ���������.
    my_jpeg_source*src=(my_jpeg_source*)cinfo->src;
    src->sof=true; // �������, ���� ���� ��� ������
  }
  METHODDEF(boolean) my_fill_input_buffer(j_decompress_ptr cinfo){// ����������, ����� ����������
    //bytes_in_buffer ��������� 0 � ��������� ������������� � ����� ������ ����������. 
    //���������� TRUE, ���� ����� ������������ �������, � FALSE ���� ��������� ������ 
    //�����/������.
    my_jpeg_source* src=(my_jpeg_source*)cinfo->src;
    (src->file)->read((char*)src->buffer,RBUF_SIZE*sizeof(JOCTET));
    size_t nbytes=(src->file)->gcount();
    // ������ ������� �� RBUF_SIZE ����
    //logout<<nbytes;
    if(nbytes<=0){// ���� �� ������ �� �������
      if(src->sof)return FALSE;	    // ������ ����
      src->buffer[0]=(JOCTET)0xFF;    // ���� ��� ������ �� �����, �� ��������� � ����� ���� 
      src->buffer[1]=(JOCTET)JPEG_EOI;// � ����� �����
      nbytes=2;
    }
    src->pub.next_input_byte=src->buffer;	// �������� ���� � �����
    src->pub.bytes_in_buffer=nbytes;	// ������� ���� ������
    src->sof=false;			// ���� �� ������
    return TRUE;
  }
  METHODDEF(void) my_skip_input_data(j_decompress_ptr cinfo, long num_bytes){// ����������, �����
    // ���������� ���������� num_bytes. � ������ ����������� ������, ��� ���������� �������������.
    my_jpeg_source*src=(my_jpeg_source*)cinfo->src;
    if(num_bytes<=0)return;// ���� ����� ���������� 0 ����
    while(num_bytes>(long)src->pub.bytes_in_buffer){// ���������� ���� �� ������ � �����������
      num_bytes-=(long)src->pub.bytes_in_buffer;  // ���, ���� num_bytes �� ������ ������ 
      my_fill_input_buffer(cinfo);	        // ������� ������
    }
    src->pub.next_input_byte+=(size_t)num_bytes;	// � ������ ������ ��������� ����������� 
    src->pub.bytes_in_buffer-=(size_t)num_bytes;	// ��������� �� ���������� �����
  }
  METHODDEF(void) my_term_source(j_decompress_ptr cinfo){// ����� ������. ���������� �������� 
    //jpeg_finish_decompress ����� ��� ������ ����� ��������. � ��� ������ ������� �� ����.
  }
  // ��� ��� ���������� �� ������������� ����� ������
  METHODDEF(void) my_stdio_src(j_decompress_ptr cinfo,STREAM* vbuff){
    my_jpeg_source*src=0;
    if(cinfo->src==0){// �������, �������� �� ������ ��� JPG ������������ ��������?
      // �������� ��������, ����� ���������� ������������� ��������� � ���������
      // �� ���������� ���������
      cinfo->src=(struct jpeg_source_mgr*)(*cinfo->mem->alloc_small) 
	((j_common_ptr)cinfo,JPOOL_PERMANENT,sizeof(my_jpeg_source));// ������� ������
      // ��� ��� ��������, � ��������� �� ���� ��������� ���������� ��������� ����������.
      // ��� ��� � ��������� �������� ������ ���������� JPG �� ����������� �� ������������
      // ��� ����. JPOOL_PERMANENT - �������� ��� ��� ������ ���������� �� ��� ����� ������
      // � �����������
      src=(my_jpeg_source*)cinfo->src;
      src->buffer=(JOCTET*)(*cinfo->mem->alloc_small) 
	((j_common_ptr)cinfo,JPOOL_PERMANENT,RBUF_SIZE*sizeof(JOCTET));// ������� 
      // ������ ��� ������� ������, ����������� �� �����
    }
    src=(my_jpeg_source*)cinfo->src;
    src->pub.init_source=my_init_source;// ����������� ����������� ������� �� ���� �������
    src->pub.fill_input_buffer=my_fill_input_buffer;
    src->pub.skip_input_data=my_skip_input_data;
    src->pub.resync_to_restart=jpeg_resync_to_restart; // ���������� ��������� �����
    src->pub.term_source=my_term_source;
    src->file=vbuff;// ������ ��������� ���� ����� ���������
    // ����������� ��������� �� ������
    src->pub.bytes_in_buffer=0;	// ������ fill_input_buffer �� ������ ��������
    src->pub.next_input_byte=0;	// ���� ����� ����������
  }
  bool IMAGE::ReadJPG(STREAM& inbuf){// ������ ������ �� JPG �����.
    inbuf.seekg(0,STREAM::beg);
    char str[20];
    inbuf.read(str,20);
    inbuf.seekg(0,STREAM::beg);
    jpeg_decompress_struct cinfo;	// ������ ��� ������������ JPG
    my_error_mgr jerr;				// ������ ��� ��������� ������
    // ����������� ��������� ������ JPEG ��������������.
    cinfo.err=jpeg_std_error(&jerr.pub);// ������������� ��������� �������� ��������� ������
    jerr.pub.error_exit=my_error_exit;	// ����������� ��������� ������� ��� ��������� ������
    // ������������� �������� ����������� setjmp �� my_error_exit
    if(setjmp(jerr.setjmp_buffer)){// ���� ��������� ������.
      jpeg_destroy_decompress(&cinfo);// ������� ���������
      return false;
    }
    jpeg_create_decompress(&cinfo);		// �������������� ���������������� ������
    my_stdio_src(&cinfo,&inbuf);		    // ��������� �������� ������
    jpeg_read_header(&cinfo,TRUE);		// ����������� ��������� jpeg
    jpeg_start_decompress(&cinfo);		// �������� ������������
    height=cinfo.output_height;			// ������ ��������� ��������
    width=cinfo.output_width;			// ������
    channels=cinfo.output_components;	// ����� ���� �� �������
    switch(cinfo.output_components){	// ������ ��������
    case 1: format=lum;	break;
    case 3: format=rgb;	break;
    default:format=und; break;	
    }
    unsigned int row_stride=cinfo.output_width*cinfo.output_components;// ����� ������
    PixelsInit();// �������� ������ ��� ������
    unsigned int nowRead=0;
    while(nowRead<height){
      JSAMPROW row_pointers[ROWS_PREAD];
      for(int row=0;row<ROWS_PREAD;row++)
	row_pointers[row]=&pixels[(nowRead+row)*row_stride];
      nowRead+=jpeg_read_scanlines(&cinfo,row_pointers,ROWS_PREAD);
    }
    jpeg_finish_decompress(&cinfo);// ��������� ������������ �����
    jpeg_destroy_decompress(&cinfo);// ������� ������ ������������
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
  bool IMAGE::ReadAJP(STREAM& inbuf){// ������ ������ �� AJP �����
    jpeg_decompress_struct cinfo;// �������� � �������������� ������ ��� ������������ JPG
    my_error_mgr jerr;
    // ����������� ��������� ������ JPEG ��������������.
    cinfo.err=jpeg_std_error(&jerr.pub);// ������������� ��������� �������� ��������� ������
    jerr.pub.error_exit=my_error_exit;	// ����������� ��������� ������� ��� ��������� ������
    // ������������� �������� ����������� setjmp �� my_error_exit
    if(setjmp(jerr.setjmp_buffer)){// ����, �����-�� ��������� ������. ������� ��������� � ������� ����
      jpeg_destroy_decompress(&cinfo);
      return false;
    }
    // ������ RGB ������
    jpeg_create_decompress(&cinfo);// �������������� ���������������� ������
    //inbuf->SetData(0,0,8,(void*)ftypes[3]);// �������� ���������, ����� �� ������� ����������
    // � ����������� �����, ����������� ��� AJP ����������
    my_stdio_src(&cinfo,&inbuf);// ��������� �������� ������
    jpeg_read_header(&cinfo,TRUE);// ����������� ��������� jpeg
    jpeg_start_decompress(&cinfo);// �������� ������������
    height=cinfo.output_height; // ������ ��������� ��������
    width=cinfo.output_width;	// ������
    channels=4;//����� ���� �� ������� ��� ������ ��������� ������
    format=rgba;//������ ��������
    unsigned int rgbChan=cinfo.output_components;//����� ���� �� ������� ��� RGB ����������
    unsigned int row_stride=width*rgbChan;// ����� ������
    unsigned char *rgbPixels=new unsigned char[row_stride*height];
    unsigned int nowRead=0;
    while(nowRead<height){
      JSAMPROW row_pointers[ROWS_PREAD];
      for(unsigned int row=0;row<ROWS_PREAD;row++)
	row_pointers[row]=&rgbPixels[(nowRead+row)*row_stride];
      nowRead+=jpeg_read_scanlines(&cinfo,row_pointers,ROWS_PREAD);
    }
    jpeg_finish_decompress(&cinfo);// ��������� ������������ �����
    jpeg_destroy_decompress(&cinfo);// ������� ������ ������������
    // ������ �����-�����	
    jpeg_create_decompress(&cinfo);// �������������� ���������������� ������
    inbuf.seekg(9,STREAM::beg);// ������ ����� � ������ AJP �����
    inbuf.seekg(FindDataStm(inbuf,SIGN_BYTES,(void*)&sign),STREAM::cur);// ����� �������� ��� ���������� �����-�����
    my_stdio_src(&cinfo,&inbuf);// ��������� �������� ������
    jpeg_read_header(&cinfo,TRUE);// ����������� ��������� jpeg
    jpeg_start_decompress(&cinfo);// �������� ������������ ����� ������
    if(cinfo.output_height<height)height=cinfo.output_height;// ���������� �������
    if(cinfo.output_width<width)width=cinfo.output_width;// ���� ����� ����� ������, �������� ��������� ��������
    unsigned int alpChan=cinfo.output_components;
    row_stride=width*alpChan;// ����� ������
    unsigned char *alpPixels=new unsigned char[row_stride*height];// �������� ������ ��� ����� ��������
    nowRead=0;
    while(nowRead<height){
      JSAMPROW row_pointers[ROWS_PREAD];
      for(unsigned int row=0;row<ROWS_PREAD;row++)
	row_pointers[row]=&alpPixels[(nowRead+row)*row_stride];
      nowRead+=jpeg_read_scanlines(&cinfo,row_pointers,ROWS_PREAD);
    }
    jpeg_finish_decompress(&cinfo);// ��������� ������������ �����
    jpeg_destroy_decompress(&cinfo);// ������� ������ ������������
    // ������ RGBA �����
    PixelsInit();// �������� ������ ��� ��������
    //*loger<<"Channels"<<alpChan<<rgbChan;
    //if(rgbChan==3 && alpChan==1);// ���������� ��������
    if((rgbChan==1)&&(alpChan==3)){	 // �� �������� ���������� ������ RGB � Alpha �������
      alpChan=1;
      rgbChan=3;
      unsigned char *env=alpPixels;// ����, ���� �������� �������
      alpPixels=rgbPixels;
      rgbPixels=env;
    }
    //*loger<<"Channels"<<alpChan<<rgbChan;
    //if(rgbChan==1 && alpChan==1);// ��� ��������� 2 ������ �������� ������
    //if(rgbChan==3 && alpChan==3);// ���� � ��� ��� ������ 3� �������
    for(unsigned int row=0;row<width*height;row++){// ��������� �������	
      *(pixels+row*channels  )=rgbChan==3?*(rgbPixels+row*3  ):*(rgbPixels+row);
      *(pixels+row*channels+1)=rgbChan==3?*(rgbPixels+row*3+1):*(rgbPixels+row);
      *(pixels+row*channels+2)=rgbChan==3?*(rgbPixels+row*3+2):*(rgbPixels+row);
      //*(pixels+row*channels+3)=0xFF;
      *(pixels+row*channels+3)=alpChan==3?(unsigned char)((*(alpPixels+row*3)+// ���� � �������� ����� ����� 
							   *(alpPixels+row*3+1)+*(alpPixels+row*3+2))/3):*(alpPixels+row);//���� RGB,������ ������� ��� �������
    }
    //Inverse();
    delete[]alpPixels;
    delete[]rgbPixels;
    return true;
  }
}
