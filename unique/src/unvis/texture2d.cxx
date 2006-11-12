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

#include "texture2d.hxx"

namespace unvis{
  using namespace unbase;
  using namespace undata;
  using namespace unogl;
  
  const GLuint TEX2D::textarget=GL_TEXTURE_2D;
  
  TEX2D::TEX2D():TEXTURE(){
    typetarget=textarget;
  }
  TEX2D::~TEX2D(){}
  
  bool TEX2D::reload(){
    RESOURCE r=resource(name,"texture");
    if(r.type==RESOURCE::stm){
      STREAM s=r.stream();
      if(s.good()){
	IMAGE m;
	if(m.Load(s)){
	  bind();
	  format=m.format;
	  chan=m.channels;
	  glTexImage2D(textarget,0,m.channels,m.width,m.height,
		       0,m.format,GL_UNSIGNED_BYTE,m.pixels);
	  OGL_DEBUG();
	  glGenerateMipmap(textarget);
	  OGL_DEBUG();
	  ubind();
	  inited=true;
	  state=STATE("texture map loaded",true);
	}else state=STATE("texture map loading error",false);
      }else state=STATE("texture map not found",false);
      r.stream(s);
    }
    return state.state;
  }
  bool TEX2D::update(){
    if(osrc!=src){
      osrc=src;
      reload();
    }
    if(!inited){
      osrc=src="Auto Generate Texture";
      init();
    }
  }
  void TEX2D::init(){
    if(!format)return;
    bind();
    chan=format;
    //cout<<"OBJECT ID: "<<this<<" SRC: "<<src<<"format: "<<format<<endl;
    glTexImage2D(textarget,0,chan,width,height,0,format,GL_UNSIGNED_BYTE,NULL);
    OGL_DEBUG();
    ubind();
    inited=true;
  }
  void TEX2D::copy(){
    int vp[4];
    glGetIntegerv(GL_VIEWPORT,vp);
    OGL_DEBUG();
    width =glTextureCompatSize(vp[2]);
    height=glTextureCompatSize(vp[3]);
    if(owidth!=width||oheight!=height){
      glTexImage2D(textarget,0,chan,width,height,0,format,GL_UNSIGNED_BYTE,NULL);
      owidth=width;
      oheight=height;
      OGL_DEBUG();
    }
    glFlush();
    //glReadBuffer(GL_FRONT);
    glCopyTexSubImage2D(textarget,0,0,0,vp[0],vp[1],vp[2],vp[3]);
    OGL_DEBUG();
    glGenerateMipmap(textarget);
    OGL_DEBUG();
  }
  
}
