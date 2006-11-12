/***************************************************************************
 *            texture2d.cpp
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

#include "texturecube.hxx"

namespace unvis{

const GLuint TEXCUBE::textarget=GL_TEXTURE_CUBE_MAP;

TEXCUBE::TEXCUBE():TEXTURE(){// Создание текстуры
  typetarget=textarget;
}
TEXCUBE::~TEXCUBE(){// Удаление текстуры
}

bool TEXCUBE::Load(string name){ // Load sides of cube texture from directory 'name'
  // 'name' send as bash:
  //      name="PATH_TO_TEXTURES/{POSITIVE_X,NEGATIVE_X,POSITIVE_Y,NEGATIVE_Y,POSITIVE_Z,NEGATIVE_Z}.EXTENSION
  /*
  FILEPATH pn=FILEPATH(name);
  for(char i=0;i<*pn;i++){
    DRES*s=DRES::get(pn[i],"tex");
    if(s){
      IMAGE m;
      if(m.Load(*s)){
	m.RevHor();
	bind();
	gluBuild2DMipmaps(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,m.channels,m.width,m.height,m.format,GL_UNSIGNED_BYTE,m.pixels);
	OGL_DEBUG();
	ubind();
	state=STATE("texture map loaded",true);
      }else state=STATE("texture map loading error",false);
    }else state=STATE("texture map not found",false);
    DRES::put(s);
  }
  */
  return state.state;
}

vec3 cubevec(char side,unsigned int size,unsigned int x,unsigned int y){
  scalar s =(scalar(x)+0.5f)/scalar(size);
  scalar t =(scalar(y)+0.5f)/scalar(size);
  scalar sc=2*s-1;
  scalar tc=2*t-1;
  vec3 v;
  switch(side){
  case 0:
    v=vec3(1,-tc,-sc);
    break;
  case 1:
    v=vec3(-1,-tc,sc);
    break;
  case 2:
    v=vec3(sc,1,tc);
    break;
  case 3:
    v=vec3(sc,-1,-tc);
    break;
  case 4:
    v=vec3(sc,-tc,1);
    break;
  case 5:
    v=vec3(-sc,-tc,-1);
    break;
  }
  v.norm();
  return v;
}

void TEXCUBE::gennorm(unsigned int size){ // Create normalization CubeMap
  bind();
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  OGL_DEBUG();
  wrap.s=TEXWRAP::clampedge;
  wrap.t=TEXWRAP::clampedge;
  filter=fullinear;
  unsigned char*pixels=new unsigned char[size*size*3]();
  for(int s=0;s<6;s++){
    for(int x=0;x<size;x++)for(int y=0;y<size;y++){
      int offs=3*(y*size+x);
      vec3 v=cubevec(s,size,x,y);
      pixels[offs+0]=128+char(scalar(127)*v.x);
      pixels[offs+1]=128+char(scalar(127)*v.y);
      pixels[offs+2]=128+char(scalar(127)*v.z);
    }
    //cout<<(int)pixels[size/2+0]<<","<<(int)pixels[size/2+1]<<","<<(int)pixels[size/2+2]<<endl;
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB+s,0,GL_RGB,size,size,0,GL_RGB,GL_UNSIGNED_BYTE,pixels);
    OGL_DEBUG();
  }
  delete pixels;
  ubind();
}

bool TEXCUBE::update(){
  if(osrc==src)return false;
  osrc=src;
  Load(src);
}

}
