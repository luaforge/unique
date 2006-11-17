/***************************************************************************
 *            texture.cpp
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

#include"texture.hxx"
#include"undata.hxx"

#include<toluaxx.h>

namespace unvis{
  using namespace undata;
  
  TEXGROUP::TEXGROUP():autoload(true){}
  TEXGROUP::TEXGROUP(bool al):autoload(al){}
  TEXGROUP::~TEXGROUP(){}
  
  __GROUP_IMPLEMENTATION_(unvis::TEXGROUP,
			  unvis::TEXTURE,
			  texture,
			  "return unvis.TEXGROUP()",
			  "local TEXTURE=unvis.TEXTURE");
  
  TEXGROUP::operator string(){
    string r="TEXGROUP{";
    int t=r.length();
    for(ITER i=pool.begin();i!=pool.end();i++)r+=(*i).first+",";
    if(t<r.length())r.erase(r.length()-1);
    r+="}";
    return r;
  }
  
  TEXTURE::COORD::COORD(unsigned int c):coord(c),mode(TEXTURE::COORD::object),
					scale(1.0,1.0,1.0,0.0),state(false){}
  TEXTURE::COORD::COORD(unsigned int c, unsigned int m):coord(c),mode(m),state(true),
							scale(1.0,1.0,1.0,0.0){}
  TEXTURE::COORD::COORD(unsigned int c, unsigned int m, vec4 s):coord(c),mode(m),scale(s),state(true){}
  void TEXTURE::COORD::set(){
    if(mode!=COORD::object && mode!=COORD::eye && mode!=COORD::sphere)return;
    switch(coord){
    case GL_S:if(state)glEnable(GL_TEXTURE_GEN_S);else glDisable(GL_TEXTURE_GEN_S);break;
    case GL_T:if(state)glEnable(GL_TEXTURE_GEN_T);else glDisable(GL_TEXTURE_GEN_T);break;
    case GL_R:if(state)glEnable(GL_TEXTURE_GEN_R);else glDisable(GL_TEXTURE_GEN_R);break;
    case GL_Q:if(state)glEnable(GL_TEXTURE_GEN_Q);else glDisable(GL_TEXTURE_GEN_Q);break;
    default: return;
    }
    OGL_DEBUG();
    glTexGeni(coord,GL_TEXTURE_GEN_MODE,mode);
    OGL_DEBUG();
    switch(mode){
    case GL_EYE_LINEAR:   glTexGenfv(coord,GL_EYE_PLANE,scale);   break;
    case GL_OBJECT_LINEAR:glTexGenfv(coord,GL_OBJECT_PLANE,scale);break;
      //case GL_SPHERE_MAP:   glTexGenfv(coord,GL_SPHERE_MAP,scale);  break;
    }
    OGL_DEBUG();
  }
  
  TEXTURE::GENCRD::GENCRD():s(GENCRD::s),t(GENCRD::t),r(GENCRD::r),q(GENCRD::q){}
  void TEXTURE::GENCRD::set(){s.set();t.set();r.set();q.set();}
  
  TEXTURE::WRAP::WRAP(int _s, int _t, int _r):s(_s),t(_t),r(_r){}
  void TEXTURE::WRAP::set(GLuint typetarget){
    glTexParameteri(typetarget,GL_TEXTURE_WRAP_S,s);
    glTexParameteri(typetarget,GL_TEXTURE_WRAP_T,t);
    glTexParameteri(typetarget,GL_TEXTURE_WRAP_R,r);
    OGL_DEBUG();
  }
  /// Texture combiner ///
  TEXTURE::FUNCPAR::FUNCPAR():target_rgb(0),target_alpha(0),rgb(0),alpha(0){}
  TEXTURE::FUNCPAR::FUNCPAR(unsigned int trgb, unsigned int ta):target_rgb(trgb),
								target_alpha(ta),rgb(0),
								alpha(0){}
  void TEXTURE::FUNCPAR::set(){
    if(rgb)  glTexEnvi(GL_TEXTURE_ENV,target_rgb,rgb);
    OGL_DEBUG();
    if(alpha)glTexEnvi(GL_TEXTURE_ENV,target_alpha,alpha);
    OGL_DEBUG();
  }
  
  TEXTURE::FUNC::FUNC():type(FUNC::modulate),combine_rgb(0),combine_alpha(0),
			scale_rgb(1.0f),scale_alpha(1.0f){
    src[0]=TEXTURE::FUNCPAR(GL_SOURCE0_RGB,GL_SOURCE0_ALPHA);
    src[1]=TEXTURE::FUNCPAR(GL_SOURCE1_RGB,GL_SOURCE1_ALPHA);
    src[2]=TEXTURE::FUNCPAR(GL_SOURCE2_RGB,GL_SOURCE2_ALPHA);
    opr[0]=TEXTURE::FUNCPAR(GL_OPERAND0_RGB,GL_OPERAND0_ALPHA);
    opr[1]=TEXTURE::FUNCPAR(GL_OPERAND1_RGB,GL_OPERAND1_ALPHA);
    opr[2]=TEXTURE::FUNCPAR(GL_OPERAND2_RGB,GL_OPERAND2_ALPHA);
  }
  void TEXTURE::FUNC::set(){
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,type);
    if(type==FUNC::combine){
      if(combine_rgb)glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,combine_rgb);
      OGL_DEBUG();
      if(combine_alpha)glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_ALPHA,combine_alpha);
      OGL_DEBUG();
      for(char i=0;i<3;i++){
	src[i].set();
	opr[i].set();
      }
      glTexEnvf(GL_TEXTURE_ENV,GL_RGB_SCALE,scale_rgb);
      OGL_DEBUG();
      glTexEnvf(GL_TEXTURE_ENV,GL_ALPHA_SCALE,scale_alpha);
      OGL_DEBUG();
    }
  }
  
  unsigned int TEXTURE::maxunits(){
    int ret;
    glGetIntegerv(GL_MAX_TEXTURE_UNITS,&ret);
    return ret;
  }
  
  TEXTURE::TEXTURE():mipmap(true),filter(TEXTURE::linear),screen(false),
		     inited(false),binded(false),format(0),storage(0){
    glGenTextures(1,&glid);
    OGL_DEBUG();
    typetarget=GL_TEXTURE_1D;
  }
  TEXTURE::~TEXTURE(){// Удаление текстуры
    glDeleteTextures(1,&glid);
    OGL_DEBUG();
  }
  
  void TEXTURE::bind(){// Биндим текстуру
    if(binded)return;
    //update();
    glEnable(typetarget);
    OGL_DEBUG();
    glBindTexture(typetarget,glid);
    if(screen)copy();
    OGL_DEBUG();
    // Switch Filtering
    switch(filter){
    case fullinear:
      glTexParameteri(typetarget,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTexParameteri(typetarget,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      break;
    case linear:
      glTexParameteri(typetarget,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
      glTexParameteri(typetarget,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
      break;
    case bilinear:
      glTexParameteri(typetarget,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTexParameteri(typetarget,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
      break;
    case trilinear:
      glTexParameteri(typetarget,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTexParameteri(typetarget,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
      break;
    case anisotropy:
      int maxAnisotropy;
      glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&maxAnisotropy);
      glTexParameteri(typetarget,GL_TEXTURE_MAX_ANISOTROPY_EXT,maxAnisotropy);
      glTexParameteri(typetarget,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTexParameteri(typetarget,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
      break;
    }
    OGL_DEBUG();
    // Set texturing Function
    func.set();
    // Wrapping
    wrap.set(typetarget);
    // Texture coordinate generation
    cgen.set();
    binded=true;
  }
  void TEXTURE::ubind(){
    if(!binded)return;
    glDisable(typetarget);
    OGL_DEBUG();
    //for(GLuint i=0;i<4;i++)if(Enabled[i])glDisable(Enabled[i]);
    glBindTexture(typetarget,0);
    OGL_DEBUG();
    binded=false;
  }
  bool TEXTURE::update(){
    if(osrc!=src){
      osrc=src;
      load();
    }
    if(!inited){
      osrc=src="Auto Generate Texture";
      init();
    }
  }
  void TEXTURE::copy(){}
  void TEXTURE::init(){}
  void TEXTURE::load(){}

  TEXTURE::operator string(){
    return "TEXTURE{}";
  }
  
  int glTextureCompatSize(int s){
    for(int i=1;true;i++){
      if(pow((double)2,(double)i)>=s){
	return pow((double)2,(double)i);
      }
    }
  }
  
}
