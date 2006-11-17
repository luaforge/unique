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
  using namespace undata;
  // Модуль пока не совсем доделан, в основном данные читаются корректно, за исключением некоторых 
  // единичных ошибок (типа неправильного расположения цветов в результате);
  // корректно читаются 24х битные RGB и 32х битные RGBA образы, 16 битные не поддерживаются 
  // (последние устарели и для OpenGL вряд ли годятся)
  // может быть его (модуля) и не будет вообще ;) нафига нам нужны ТГА имейджи по 1 Мб

  const int IMTGA::sign=0x00020000; // ! Байты реверсированы (перевернуты)
  const char IMTGA::className[]="TGA_IMAGE";

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
    dest();
    init();
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

}
