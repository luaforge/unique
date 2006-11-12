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
 *  Модуль чтения данных TGA из виртуального буффера, специально для Eline Engine    *
 *   Это Free Ware & Open Source, можете использовать как угодно, за последствия     *
 *    автор, т.е. FeniX, ответственности не несет.    Для подробной информации,      *
 *     смотреть ReadMe.txt,  http://aulora3d.trg.ru/   и комментарии в сурсе;        *
 *      по вопросам, а также если найдете ошибки писать:   tonder@trktvs.ru          *
 *************************************************************************************/

#include "image.hxx"

namespace unvis{

// Модуль пока не совсем доделан, в основном данные читаются корректно, за исключением некоторых 
// единичных ошибок (типа неправильного расположения цветов в результате);
// корректно читаются 24х битные RGB и 32х битные RGBA образы, 16 битные не поддерживаются 
// (последние устарели и для OpenGL вряд ли годятся)
// может быть его (модуля) и не будет вообще ;) нафига нам нужны ТГА имейджи по 1 Мб

const int IMTGA::sign=0x00020000; // ! Байты реверсированы (перевернуты)
const char IMTGA::className[]="TGA_IMAGE";

#define MY_FUNC_READ_TGA
#ifdef MY_FUNC_READ_TGA // Если используем мою функцию чтения TGA

bool IMAGE::ReadTGA(STREAM& inbuf){// Моя функция для чтения TGA
  unsigned char header[18];
  inbuf.seekg(0,STREAM::beg);// Сбрасываем буффер на начало
  inbuf.read((char*)header,18);// Читаем заголовочную инфу
  width=header[12]+header[13]*256;// Ширина образа
  height=header[14]+header[15]*256;// Высота образа
  switch(header[16]){
  case 16:channels=3; format=rgb;break;
  case 24:channels=3; format=rgb;break;
  case 32:channels=4; format=rgba;break;
  default: return false;
  }
  pixels=new unsigned char[width*height*channels];
  if(!pixels)return false;
  inbuf.seekg(header[0],STREAM::cur);
  switch(header[2]){// Упакованы ли наши данные
  case 2: inbuf.read(pixels,width*height*channels); break; // Не упакованы, читаем напрямую
  case 10:{// Упакованы, по блокам будем читать
    unsigned char BlockInfo,pix[4];
    char WhatItIs;
    unsigned int  NumPixels;
    for(unsigned int i=0;i<width*height;){// поехали (как сказал кто-то всем нам знакомый)
      inbuf.read(&BlockInfo,1);// Читаем информацию о блоке
      WhatItIs=BlockInfo&0x80;
      NumPixels=BlockInfo&0x7F;
      if(WhatItIs){//Если запакованные данные
	// Это, чтобы не дублировать идущие подряд одинаковые пиксели в образе
	// разработчики решили просто назвать один пиксель и указать сколько их там
	inbuf.read((char*)pix,channels);// Читаем пиксель
	for(unsigned int k=0;k<NumPixels+1;k++){
	  pixels[i*channels+0]=pix[2];// Переворачиваем BV{J
	  pixels[i*channels+1]=pix[1];
	  pixels[i*channels+2]=pix[0];
	  if(channels==4)pixels[i*channels+3]=pix[3];
	  i++;//Увеличиваем счетчик кол-ва пикселей
	}
      }else{ //Если не запакованные данные
	for(unsigned int k=0;k<NumPixels+1;k++){
	  inbuf.read((char*)pix,channels);// Читаем пиксель
	  pixels[i*channels+0]=pix[2];// Переворачиваем BV{J
	  pixels[i*channels+1]=pix[1];
	  pixels[i*channels+2]=pix[0];
	  if(channels==4)pixels[i*channels+3]=pix[3];
	  i++;//Увеличиваем счетчик кол-ва пикселей
	}
      }
    }
  } break;
  default: delete pixels; return false; // Какая-то невозможная ошибка (например сфабрикована вирусами)
  }
  return true;
}

#else // Используем функцию, написанную моим другом
// Не советую, она не все корректно читает
bool IMAGE::ReadTGA(STREAM& inbuf){
  unsigned int l,size;
  unsigned char rep,*buf,*ptr,header[18];
  inbuf.seekg(0,STREAM::beg);
  inbuf->ReadData(18,header);// Читаем заголовочную инфу
  width=header[12]+header[13]*256;
  height=header[14]+header[15]*256;
  switch(header[16]){
  case 16:channels=3; format=IM_RGB;break;
  case 24:channels=3; format=IM_RGB;break;
  case 32:channels=4; format=IM_RGBA;break;
  default: return false;
  }
  size=width*height*channels;
  buf=new unsigned char[size];
  pixels=new unsigned char[width*height*4];
  if(!pixels || !buf)return false;
  *inbuf+=header[0];
  unsigned int i,j,k;
  switch(header[2]) {
  case 2: inbuf->ReadData(size,buf); break;
  case 10: i=0; ptr=buf;
    while(i<size){
      inbuf->ReadData(1,&rep);
      if(rep&0x80){
	rep^=0x80;
	inbuf->ReadData(channels,ptr);
	ptr+=channels;
	for(j=0;j<rep*channels;j++){
	  *ptr=*(ptr-channels);
	  ptr++;
	} i+=channels*(rep+1);
      }else{
	k=channels*(rep+1);
	inbuf->ReadData(k,ptr);
	ptr+=k;	i+=k;
      }
    }break;
  default:
    delete buf;
    delete pixels;
    return false;
  }
  for(i=0,j=0;i<size;i+=channels,j+=4){
    pixels[j]=buf[i+2];
    pixels[j+1]=buf[i+1];
    pixels[j+2]=buf[i];
    if(channels==4)pixels[j+3]=buf[i+3];
    else pixels[j+3]=255;
  }
  if(!(header[17]&0x20)) {
    for(j=0,k=width*4;j<height/2;j++){
      for(i=0;i<width*4;i++){
	l=pixels[j*k+i];
	pixels[j*k+i]=pixels[(height-j-1)*k+i];
	pixels[(height-j-1)*k+i]=l;
      }
    }
  }
  delete buf;
  return true;
}
#endif

}
