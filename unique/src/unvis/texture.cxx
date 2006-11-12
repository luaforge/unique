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

#include"toluaxx.h"

namespace unvis{

  TEXTURES::TEXTURES(){}
  TEXTURES::~TEXTURES(){}
  void TEXTURES::operator()(string&n,TEXTURE*&t){
    
  }
  TEXTURE* TEXTURES::get(string n){
    /*
      if(array.find(name)!=array.end())return array[name];else{ // Try load
      DRES* s=DRES::get(name+".lua","tex");
      if(s){
      lua_State* L=tolua_state();
      string source=s->str(); source+="\n_texret_."+name+"="+"ret\n";
      lua_pushstring(L,"_texret_");
      tolua_pushusertype(L,(void*)this,"TEXTURES");
      lua_settable(L,LUA_GLOBALSINDEX);
      lua_dobuffer(L,source.data(),source.length(),s->name.data());
      DRES::put(s);
      if(array.find(name)!=array.end())return array[name];
      }
      return NULL;
      }
    */
    if(array.find(n)!=array.end())return array[n];else return NULL;
  }
  void TEXTURES::set(string name,TEXTURE* node){
    if(node)array.insert(std::make_pair(name,node));else array.erase(name);
  }
  TEXTURES::operator string(){string ret="";for(ITER i=array.begin();i!=array.end();i++){ret+=(*i).first+",";} ret.erase(ret.length()-1);return ret;}
  
  TEXCRD::TEXCRD(GLenum c):coord(c),mode(TEXCRD::object),scale(vec4(1.0,1.0,1.0,0.0)),state(false){}
  TEXCRD::TEXCRD(GLenum c,GLenum m):coord(c),mode(m),scale(vec4(1.0,1.0,1.0,0.0)),state(true){}
  TEXCRD::TEXCRD(GLenum c,GLenum m,vec4 s):coord(c),mode(m),scale(s),state(true){}
  void TEXCRD::set(){
    if(mode!=TEXCRD::object && mode!=TEXCRD::eye && mode!=TEXCRD::sphere)return;
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
  
  TEXCGEN::TEXCGEN():s(TEXCRD::s),t(TEXCRD::t),r(TEXCRD::r),q(TEXCRD::q){}
  void TEXCGEN::set(){s.set();t.set();r.set();q.set();}
  
  TEXWRAP::TEXWRAP(GLint _s,GLint _t,GLint _r):s(_s),t(_t),r(_r){}
  void TEXWRAP::set(GLuint typetarget){
    glTexParameteri(typetarget,GL_TEXTURE_WRAP_S,s);
    glTexParameteri(typetarget,GL_TEXTURE_WRAP_T,t);
    glTexParameteri(typetarget,GL_TEXTURE_WRAP_R,r);
    OGL_DEBUG();
  }
  /// Texture combiner ///
  TEXFUNCPAR::TEXFUNCPAR():target_rgb(0),target_alpha(0),rgb(0),alpha(0){}
  TEXFUNCPAR::TEXFUNCPAR(GLuint trgb, GLuint ta):target_rgb(trgb),
						 target_alpha(ta),rgb(0),
						 alpha(0){}
  void TEXFUNCPAR::set(){
    if(rgb)  glTexEnvi(GL_TEXTURE_ENV,target_rgb,rgb);
    OGL_DEBUG();
    if(alpha)glTexEnvi(GL_TEXTURE_ENV,target_alpha,alpha);
    OGL_DEBUG();
  }
  
  TEXFUNC::TEXFUNC():type(TEXFUNC::modulate),combine_rgb(0),combine_alpha(0),
		     scale_rgb(1.0f),scale_alpha(1.0f){
    src[0]=TEXFUNCPAR(GL_SOURCE0_RGB,GL_SOURCE0_ALPHA);
    src[1]=TEXFUNCPAR(GL_SOURCE1_RGB,GL_SOURCE1_ALPHA);
    src[2]=TEXFUNCPAR(GL_SOURCE2_RGB,GL_SOURCE2_ALPHA);
    opr[0]=TEXFUNCPAR(GL_OPERAND0_RGB,GL_OPERAND0_ALPHA);
    opr[1]=TEXFUNCPAR(GL_OPERAND1_RGB,GL_OPERAND1_ALPHA);
    opr[2]=TEXFUNCPAR(GL_OPERAND2_RGB,GL_OPERAND2_ALPHA);
  }
  void TEXFUNC::set(){
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,type);
    if(type==TEXFUNC::combine){
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
    typetarget=textarget;
  }
  TEXTURE::~TEXTURE(){// Удаление текстуры
    glDeleteTextures(1,&glid);
    OGL_DEBUG();
  }
  const GLuint TEXTURE::textarget=GL_TEXTURE_1D;
  
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
  bool TEXTURE::update(){}
  void TEXTURE::copy(){}
  void TEXTURE::init(){}
  
  int glTextureCompatSize(int s){
    for(int i=1;true;i++)if(pow((double)2,(double)i)>=s)return pow((double)2,(double)i);
  }
  
}
