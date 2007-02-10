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

//#define DONT_INCLUDE_IMAGELIBS // ��������� ������������� ���������� ����������� ����������
//#include <zlib.h>
//#include <libpng/pngconf.h>
#define PNGAPI
#include"image.hxx"
#include<png.h>

namespace unvis{
  using namespace undata;

#define NUM_SIGN 8

  const int IMPNG::sign=0x474E5089; // ! ����� ������������� (�����������)
  const char IMPNG::className[]="PNG_IMAGE";

  void my_png_read_func(png_structp png_ptr,png_bytep data,png_size_t slength){// ������� ��� ������
    // ������ �� ������������ ������, ������� ����� ������������ ���������� PNG. �� ����
    // �������� ��������� �� ��������� ���������� ���������� � ���������� � ����� ����, �������
    // ����� ��������. ����������� ������ ��������� � data.
    STREAM* buffer=(STREAM*)png_get_io_ptr(png_ptr);
    buffer->read((char *)data,slength);
  }
  
# define IMAGE_DEBUG(n) cout<<#n<<endl;

  bool IMAGE::ReadPNG(STREAM& inbuf){// ������ PNG ������ �� ������������ ������.
    inbuf.seekg(0,STREAM::beg);			//���������� �����
    png_byte sig[NUM_SIGN];
    inbuf.read(sig,sizeof(png_byte)*NUM_SIGN);// ��������� ���������, �� ��� ���������,
    //IMAGE_DEBUG(1);
    int gc=inbuf.gcount();
    if(!png_check_sig(sig,NUM_SIGN))return false;// �� ����� ���������� ���� ��� ������� �� ������ ������
    png_structp png_ptr=png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);// ������� ����������
    //��������� png ��� ������ � ������
    //IMAGE_DEBUG(2);
    if(!png_ptr)return false;// ������� ��������� � ����������� � ���������� �������
    png_infop info_ptr=png_create_info_struct(png_ptr);
    if(!info_ptr){// ���� ���-�� ��� �������� ��������� ������, ������� ���������� ���������
      png_destroy_read_struct(&png_ptr,0,0);
      return false;
    }
    //IMAGE_DEBUG(3);
    png_set_read_fn(png_ptr,(void*)&inbuf,my_png_read_func);// ����������� ���������� �� ���
    // ������ ������ ������
    png_set_sig_bytes(png_ptr,NUM_SIGN);// ������� ����������, ��� �� ��� ������ NUM_SIGN ����
    png_read_info(png_ptr,info_ptr);// ������ ��� ���������� � �����
    // ��� ������� ���������� ���� �� info_ptr
    int bit_depth=0;  // ������� ����� (������ �� �������, ����� ���� 1, 2, 4, 8, 16)
    int color_type=0; // ��������� ����� ������ ������������:
    // PNG_COLOR_TYPE_GRAY, PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE,
    // PNG_COLOR_TYPE_RGB, PNG_COLOR_TYPE_RGB_ALPHA...
    // ��������� 3 ��������� ����� ���� ������ � ����������: ��� �������, ��� ���������� � ��� ��������
    png_get_IHDR(png_ptr,info_ptr,(unsigned long*)&width,(unsigned long*)&height,&bit_depth,&color_type,0,0,0);
    // ����, ����� png �������� �� ���� ������� ��� ��� �����, ����������� ��� ����������� � ������ ���
    // png ������ ����� ��������� 16 ��� �� �����, �� ��� ����� ������ 8, ������� ������ �����
    if(bit_depth==16)png_set_strip_16(png_ptr);
    // ����������� ���� ���� �� �������� ������� � ���������� RGB
    if(color_type==PNG_COLOR_TYPE_PALETTE && bit_depth<=8)png_set_palette_to_rgb(png_ptr);
    // ���� � ���������� ������ ��� �� ����� ��� 8, �� ��������� � ����������� 8-�������
    if(color_type==PNG_COLOR_TYPE_GRAY && bit_depth<8)png_set_gray_1_2_4_to_8(png_ptr);
    // � ��������� ������ �����-�����
    if(png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS))png_set_tRNS_to_alpha(png_ptr);
    // ��� ��� ����� ������� ����� �������� png_set_expand(png_ptr);
    // ��� �������������� ��������� �������� � RGB ������, ���� ������� ���:
    if(color_type==PNG_COLOR_TYPE_GRAY || color_type==PNG_COLOR_TYPE_GRAY_ALPHA)
      png_set_gray_to_rgb(png_ptr);
    // ��� ����������� ����������� ��������, ����� ��������� ����� � ����������� �� ��������
    // ��������, �� �� ����� �����:
    // 2.2 - ������ ��� PC ��������� � ���������� �������
    // 2.0 - ��� PC � ������ �������
    // �� 1.7 �� 1.0 - ��� ������ MacOS
    double gamma=0.0f;
    if(png_get_gAMA(png_ptr,info_ptr,&gamma))png_set_gamma(png_ptr,2.2,gamma);// ���� ����
    // ���������� � ����� � �����, �� ������������� �� 2.2
    else png_set_gamma(png_ptr,2.2,0.45455);// ����� ������ ��������� ����� ���
    // ������ � 0.45455 (good guess for GIF images on PCs)
    png_read_update_info(png_ptr,info_ptr);// ����� ���� �������������, �������� ����������
    // ����� �������� ��� ������� � ��������� ����������� ��������
    png_get_IHDR(png_ptr,info_ptr,(unsigned long*)&width,(unsigned long*)&height,&bit_depth,&color_type,0,0,0);
    // �������� ���-�� ������� �� �������
    // ����� ����: 1 (GRAY, PALETTE), 2 (GRAY_ALPHA), 3 (RGB), 4 (RGB_ALPHA ��� RGB + filler byte)
    channels=png_get_channels(png_ptr,info_ptr);// ���������� ���-�� ���� ������ ��� ���� ����� �������� ������
    png_uint_32 row_bytes=png_get_rowbytes(png_ptr,info_ptr);
    dest();
    init();// ������, �� ����� �������� ������ ����� �������� ��������
    png_byte **row_pointers=new png_byte*[height];// �������� ������, ��� ���������� �� ������ ������
    // ������������ ������ ���������� �� �������, � ����������� � ������ (res)
    // �.�. ����������� ������������, �� ��������� ���� ����� �����
    for(unsigned int i=0;i<height;i++)row_pointers[height-i-1]=pixels+i*row_bytes;
    // ������ ��������
    png_read_image(png_ptr,row_pointers);
    // ������ �������������� ���������� � ����� (�� ����� ���� ���������� ��)
    png_read_end(png_ptr,0);
    // ����������� ������ �� ���������� �� ������
    delete[]row_pointers;
    // ����������� ������ ���������� ��� ���������� libpng
    png_destroy_read_struct(&png_ptr,0,0);
    // ���������� ���������� � ��������
    switch(color_type){// ������������� ������ ��������
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
