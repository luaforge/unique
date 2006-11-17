/***************************************************************************
 *            tga.cpp
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

/*************************************************************************************
 *  ������ ������ ������ TGA �� ������������ �������, ���������� ��� Eline Engine    *
 *   ��� Free Ware & Open Source, ������ ������������ ��� ������, �� �����������     *
 *    �����, �.�. FeniX, ��������������� �� �����.    ��� ��������� ����������,      *
 *     �������� ReadMe.txt,  http://aulora3d.trg.ru/   � ����������� � �����;        *
 *      �� ��������, � ����� ���� ������� ������ ������:   tonder@trktvs.ru          *
 *************************************************************************************/

#include "image.hxx"

namespace unvis{
  using namespace undata;
  // ������ ���� �� ������ �������, � �������� ������ �������� ���������, �� ����������� ��������� 
  // ��������� ������ (���� ������������� ������������ ������ � ����������);
  // ��������� �������� 24� ������ RGB � 32� ������ RGBA ������, 16 ������ �� �������������� 
  // (��������� �������� � ��� OpenGL ���� �� �������)
  // ����� ���� ��� (������) � �� ����� ������ ;) ������ ��� ����� ��� ������� �� 1 ��

  const int IMTGA::sign=0x00020000; // ! ����� ������������� (�����������)
  const char IMTGA::className[]="TGA_IMAGE";

  bool IMAGE::ReadTGA(STREAM& inbuf){// ��� ������� ��� ������ TGA
    unsigned char header[18];
    inbuf.seekg(0,STREAM::beg);// ���������� ������ �� ������
    inbuf.read((char*)header,18);// ������ ������������ ����
    width=header[12]+header[13]*256;// ������ ������
    height=header[14]+header[15]*256;// ������ ������
    switch(header[16]){
    case 16:channels=3; format=rgb;break;
    case 24:channels=3; format=rgb;break;
    case 32:channels=4; format=rgba;break;
    default: return false;
    }
    dest();
    init();
    if(!pixels)return false;
    inbuf.seekg(header[0],STREAM::cur);
    switch(header[2]){// ��������� �� ���� ������
    case 2: inbuf.read(pixels,width*height*channels); break; // �� ���������, ������ ��������
    case 10:{// ���������, �� ������ ����� ������
      unsigned char BlockInfo,pix[4];
      char WhatItIs;
      unsigned int  NumPixels;
      for(unsigned int i=0;i<width*height;){// ������� (��� ������ ���-�� ���� ��� ��������)
	inbuf.read(&BlockInfo,1);// ������ ���������� � �����
	WhatItIs=BlockInfo&0x80;
	NumPixels=BlockInfo&0x7F;
	if(WhatItIs){//���� ������������ ������
	  // ���, ����� �� ����������� ������ ������ ���������� ������� � ������
	  // ������������ ������ ������ ������� ���� ������� � ������� ������� �� ���
	  inbuf.read((char*)pix,channels);// ������ �������
	  for(unsigned int k=0;k<NumPixels+1;k++){
	    pixels[i*channels+0]=pix[2];// �������������� BV{J
	    pixels[i*channels+1]=pix[1];
	    pixels[i*channels+2]=pix[0];
	    if(channels==4)pixels[i*channels+3]=pix[3];
	    i++;//����������� ������� ���-�� ��������
	  }
	}else{ //���� �� ������������ ������
	  for(unsigned int k=0;k<NumPixels+1;k++){
	    inbuf.read((char*)pix,channels);// ������ �������
	    pixels[i*channels+0]=pix[2];// �������������� BV{J
	    pixels[i*channels+1]=pix[1];
	    pixels[i*channels+2]=pix[0];
	    if(channels==4)pixels[i*channels+3]=pix[3];
	    i++;//����������� ������� ���-�� ��������
	  }
	}
      }
    } break;
    default: delete pixels; return false; // �����-�� ����������� ������ (�������� ������������ ��������)
    }
    return true;
  }

}
