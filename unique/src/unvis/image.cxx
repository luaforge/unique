/***************************************************************************
 *            image.cpp
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

#include "image.hxx"

namespace unvis{
  const char IMAGE::className[]="IMAGE";
  const int IMAGE::sign=0x00000000;
  
  // Сигнатуры графических файлов
  /*char IMAGE::sig_fmt[][8]={
    {0x00,0x00,0x02,0x00},// Начало TGA файла
    {0x89,0x50,0x4E,0x47},// Начало PNG файла
    {0xFF,0xD8,0xFF,0xE0},// Начало JPG файла
    {0xFF,0xD8,0xFF,0xE1},// Начало AJP* файла
    {NULL,NULL,NULL,NULL}
    // Мой формат образа текстуры (Сплит обычного JPG и JPG градации серого в качестве альфа канала)
    };*/

  IMAGE::IMAGE(){
    pixels=NULL;
  }
  IMAGE::~IMAGE(){
  }
  void IMAGE::PixelsInit(){
    if(pixels==NULL)pixels=new unsigned char[width*height*channels];
  }
  void IMAGE::PixelsDest(){
    if(pixels!=NULL){
      delete []pixels;
      pixels=NULL;
    }
  }

  bool IMAGE::Read(STREAM& res){
    return false;
  }

#define SIGN_BYTES 4
  /*bool IMAGE::CheckType(DRES* buf){
   *buf=0;
   char chr[SIGN_BYTES];
   buf->Read(chr,SIGN_BYTES);
   *buf=0;
   printf("%x",sign);
   return bool(memcmp(chr,&sign,SIGN_BYTES)==0);
   }*/
  //typedef bool (IMAGE::*imRead)(DRES* buf);
  // Чтение данных различных форматов
  /*#define CHLOADIM(type,sg,buf){ \
    if(memcmp(sg,&(((type*)this)->sign),4)==0){ \
    printf(#type); \
    bool (type::*fc)(DRES* buf)=type::Read; \
    return (((type*)this)->*fc)(buf); \
    } \
    }*/
  /*#define CHLOADIM(type,sg,buf){ \
    if(memcmp(sg,&(((type*)this)->sign),4)==0){ \
    return ((type*)this)->Read(buf); \
    } \
    }

    //type* im=(type*)this; \
    //return ((type*)this)->Read(buf); \

    #define LOADIM(type,buf){ \
    if(type::CheckType(buf)){ ((type*)this)->Read(buf); return true; } \
    }
  */
  bool IMAGE::Load(STREAM& ibuf){// Чтение из любого формата
    if(!ibuf.good())return false;
    unsigned int i;
    //for(i=0;i)
    //if(IMPNG::CheckType(buf)){ ((IMPNG*)this)->Read(buf); return true;
    //LOADIM(IMPNG,buf)
    ibuf.seekg(0,STREAM::beg);
    char sg[4];
    ibuf.read(sg,4);
    if(ibuf.gcount()!=4)return false;
    if(memcmp(sg,&(((IMPNG*)this)->sign),4)==0){
      return ReadPNG(ibuf);
    }
    if(memcmp(sg,&(((IMTGA*)this)->sign),4)==0){
      return ReadTGA(ibuf);
    }
    if(memcmp(sg,&(((IMJPG*)this)->sign),4)==0){
      return ReadJPG(ibuf);
    }
    if(memcmp(sg,&(((IMAJP*)this)->sign),4)==0){
      return ReadAJP(ibuf);
    }
    //cout<<"BAD:"<<ibuf.name<<endl;
    return false;
  }
  //#define FORMATIM(type,buf){ \
  //	if(type::CheckType(buf))return new type(); \
  //}

  //#define FORMATIM(type,buf){ \
  //  if(memcmp(buf,&(type::sign),SIGN_BYTES)==0)return new type(); \
  //}
  /*
    IMAGE* IMAGE::FORMAT(DRES* buf){
    char bf[4];
    (*buf)=0;
    int rez=buf->Read(bf,4);
    (*buf)=0;
    if(IMPNG::CheckType(buf))return new IMPNG();
    //if(memcmp(buf,&(IMPNG::sign),4)==0)return new IMPNG();
    //FORMATIM(IMPNG,bf);
    //FORMATIM(IMTGA,bf);
    //FORMATIM(IMJPG,bf);
    //FORMATIM(IMAJP,bf);
    return NULL;
    }*/
  bool IMAGE::ReplPix(unsigned int ox,unsigned int oy,unsigned int tx,unsigned int ty){
    // Меняет местами пиксели с заданными координатами
    unsigned char bf;
    if(ox>=width||tx>=width||oy>=height||ty>height)return false;
    for(unsigned int i=0;i<channels;i++){
      bf=pixels[(ox+oy*width)*channels+i];
      pixels[(ox+oy*width)*channels+i]=pixels[(tx+ty*width)*channels+i];
      pixels[(tx+ty*width)*channels+i]=bf;
    }
    return true;
  }
  bool IMAGE::Reverse(int orr){
    unsigned int i,j;
    switch(orr){
    case ver_line:
      for(i=0;i<(unsigned int)(width/2);i++){
	for(j=0;j<height;j++){
	  ReplPix(i,j,width-i-1,j);
	}
      } break;
    case hor_line:
      for(i=0;i<(unsigned int)(height/2);i++){
	for(j=0;j<width;j++){
	  ReplPix(j,i,j,height-i-1);
	}
      } break;
    default: return false; break;
    }
    return true;
  }

  void IMAGE::RevHor(){
    unsigned int half_height=(unsigned int)(0.5*height);
    for(unsigned int i=0;i<width;i++)for(unsigned int j=0;j<half_height;j++)ReplPix(i,j,i,height-j-1);
  }
  void IMAGE::AddAlpha(unsigned char *buf,unsigned int stp){
    unsigned int oldchan=channels;
    channels++;
    unsigned char *newpixels=new unsigned char[width*height*channels];
    unsigned int i;
    switch(format){
    case lum:
      format=luma;
      for(i=0;i<width*height;i++){
	newpixels[i*channels]=pixels[i*oldchan];
	newpixels[i*channels+1]=buf[i*stp];
      }
      break;
    case rgb:
      format=rgba;
      for(i=0;i<width*height;i++){
	newpixels[i*channels]=pixels[i*oldchan];
	newpixels[i*channels+1]=pixels[i*oldchan+1];
	newpixels[i*channels+2]=pixels[i*oldchan+2];
	newpixels[i*channels+3]=buf[i*stp];
      }
      break;
    }
    delete []pixels;
    pixels=newpixels;
  }
  void IMAGE::Inverse(){
    if(channels==3)for(unsigned int i=0;i<width*height*channels;i++)
		     pixels[i]=255-pixels[i];
    // инвертируем цвета (не знаю почему, но цвета в png инверсные)
    if(channels==2)for(unsigned int i=0;i<width*height*channels;i++)
		     if((i+1)%2)pixels[i]=255-pixels[i];
    if(channels==4)for(unsigned int i=0;i<width*height*channels;i++)
		     if((i+1)%4)pixels[i]=255-pixels[i];
  }

}
