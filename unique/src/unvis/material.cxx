/***************************************************************************
 *            material.cpp
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

#include"material.hxx"
#include"undata.hxx"

#include<toluaxx.h>

namespace unvis{
  using namespace unogl;
  
  MATGROUP::MATGROUP():MATERIAL(),autoload(true){}
  MATGROUP::MATGROUP(bool al):MATERIAL(),autoload(al){}
  MATGROUP::~MATGROUP(){}

  __GROUP_IMPLEMENTATION_(unvis::MATGROUP,
			  unvis::MATERIAL,
			  material,
			  "return unvis.MATGROUP()",
			  "local MATERIAL=unvis.MATERIAL");
  
  MATGROUP::operator string(){
    string r="MATGROUP{";
    {
      int b=r.length();
      for(ITER i=pool.begin();i!=pool.end();i++){
	r+=i->first+"="+static_cast<string>(*(i->second))+",";
      }
      if(r.length()>b)r.erase(r.length()-1);
    }
    r+="}";
    return r;
  }
  
  MATERIAL::COLOR::COLOR():emission(vec4(0.0,0.0,0.0,1.0)),ambient(vec4(0.2,0.2,0.2,1.0)),diffuse(vec4(0.8,0.8,0.8,1.0)),specular(vec4(0.0,0.0,0.0,1.0)),shininess(0.0f){}
  void MATERIAL::COLOR::bind(GLuint side){
    glMaterialfv(side,GL_EMISSION, emission );
    glMaterialfv(side,GL_AMBIENT,  ambient  );
    glMaterialfv(side,GL_DIFFUSE,  diffuse  );
    glMaterialfv(side,GL_SPECULAR, specular );
    glMaterialf (side,GL_SHININESS,shininess);
    OGL_DEBUG();
  }
  void MATERIAL::COLOR::ubind(){
    OGL_DEBUG();
  }
  
  MATERIAL::TEXMAP::TEXMAP():emission(NULL),ambient(NULL),diffuse(NULL),specular(NULL){}
  TEXTURE *& MATERIAL::TEXMAP::operator[](int i){
    i=i>0?i:0;
    i=i<3?i:3;
    return map[i];
  }
  void MATERIAL::TEXMAP::bind(){
    for(GLuint i=0;i<4;i++){
      if(map[i]!=NULL){
	glActiveTexture(GL_TEXTURE0+i);
	OGL_DEBUG();
	map[i]->bind();
      }
      OGL_DEBUG();
    }
  }
  void MATERIAL::TEXMAP::ubind(){
    for(GLuint i=0;i<4;i++){
      if(map[i]!=NULL){
	glActiveTexture(GL_TEXTURE0+i);
	OGL_DEBUG();
	map[i]->ubind();
      }
      OGL_DEBUG();
    }
  }
  
  MATERIAL::MATERIAL():parent(NULL),light(true),shader(NULL){}
  MATERIAL::~MATERIAL(){}
  void MATERIAL::bind(){
    glPushAttrib(GL_COLOR_BUFFER_BIT|GL_CURRENT_BIT|GL_ENABLE_BIT|GL_LIGHTING_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    if(light){
      glEnable(GL_LIGHTING);
      glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
      color.bind(GL_FRONT_AND_BACK);
    }else{
      glDisable(GL_LIGHTING);
      glColor4fv(color.emission);
      //glEnable(GL_COLOR_MATERIAL);
      //glColorMaterial(side,GL_DIFFUSE);
    }
    OGL_DEBUG();
    //cout<<side<<" "<<GL_FRONT<<"\n";
    //glEnable(GL_COLOR_MATERIAL);
    //glColorMaterial(side,GL_DIFFUSE);
    //glDisable(GL_COLOR_MATERIAL);
    texture.bind();
    OGL_DEBUG();
    if(shader)shader->bind();
    OGL_DEBUG();
  }
  void MATERIAL::ubind(){
    color.ubind();
    OGL_DEBUG();
    texture.ubind();
    OGL_DEBUG();
    if(shader)shader->ubind();
    OGL_DEBUG();
    glPopAttrib();
  }
  MATERIAL::operator string(){
    string r="MATERIAL{";
    r+="}";
    return r;
  }
}
