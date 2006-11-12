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
  using namespace undata;
  using namespace unmath;
  using namespace unogl;

  MATGROUP::MATGROUP(){}
  MATGROUP::~MATGROUP(){}
  void MATGROUP::operator()(string&n,MATERIAL*&m){
    ITER i;
    if(n=="")i=array.begin();
    else{
      i=array.find(n);
      if(i==array.end()){n="";m=NULL;return;}
      i++; for(;i->second==NULL&&i!=array.end();i++);
      if(i==array.end()){n="";m=NULL;return;}
    }
    n=i->first;
    m=i->second;
  }
  /*
    set self as environ index
    wrap script content in function
    call function return value in self environ index
   */
  MATGROUP* __material_load_root_;
  string    __material_load_name_;
  int __material_load_handler_(lua_State*L){
    if(!__material_load_root_)return 0;
                        // stack: loadfunc
    tolua_pushusertype(L,__material_load_root_,"MATGROUP");
                        // stack: loadfunc rootgroup
    tolua_pushstring(L,__material_load_name_.data());
                        // stack: loadfunc rootgroup entname
    lua_pushvalue(L,1); // stack: loadfunc rootgroup entname loadfunc
    lua_pushvalue(L,2); // stack: loadfunc rootgroup entname loadfunc rootgroup
    lua_call(L,1,1);    // stack: loadfunc rootgroup entname entobj
    lua_insert(L,-2);   // stack: loadfunc rootgroup entobj entname
    lua_settable(L,-3); // stack: loadfunc rootgroup
    return 0;
  }
  string MATGROUP::hiername(string n){
    string r;
    if(parent)r+=parent->hiername();
    if(r.length()>0)r+="."; r+=name;
    if(n.length()>0){r+=".";r+=n;}
  }
  MATERIAL* MATGROUP::get(string n){
    if(array.find(n)==array.end()){ // Try load
      string pn=hiername(n);
      
      RESOURCE r=resource(pn,"material");
      lua_State* L=tolua_state();
      
      lua_pushcfunction(L,__material_load_handler_);
      lua_setfield(L,LUA_GLOBALSINDEX,"__material_load_handler_");
      
      if(r.type==RESOURCE::dir){
	string l="__material_load_handler_(function(self) return MATGROUP() end)";
	string b="material `"; b+=pn; b+="` script";
	__material_load_root_=this;
	luaL_loadbuffer(L,l.data(),l.length(),b.data());
      }else if(r.type==RESOURCE::stm){
	STREAM& s=r.stream(STREAM::inp);
	if(s.good()){
	  string l=s.read();
	  string b="material `"; b+=pn; b+="` script";
	  __material_load_root_=this;
	  luaL_loadbuffer(L,l.data(),l.length(),b.data());
	  r.stream(s);
	  //cout<<"+++"<<source<<"+++"<<endl;
	}
      }
    }
    if(array.find(name)==array.end()) return NULL; else return array[name];
  }
  void MATGROUP::set(string name,MATERIAL* node){
    if(node){
      array[name]=node;
      array[name]->parent=this;
    }else array.erase(name);
  }
  MATGROUP::operator string(){string ret="";for(ITER i=array.begin();i!=array.end();i++){ret+=(*i).first+",";} ret.erase(ret.length()-1);return ret;}
  
  MATERIAL::COLOR::COLOR():emission(vec4(0.0,0.0,0.0,1.0)),ambient(vec4(0.2,0.2,0.2,1.0)),diffuse(vec4(0.8,0.8,0.8,1.0)),specular(vec4(0.0,0.0,0.0,1.0)),shininess(0.0f){}
  void MATERIAL::COLOR::set(GLuint side){
    glMaterialfv(side,GL_EMISSION, emission );
    glMaterialfv(side,GL_AMBIENT,  ambient  );
    glMaterialfv(side,GL_DIFFUSE,  diffuse  );
    glMaterialfv(side,GL_SPECULAR, specular );
    glMaterialf (side,GL_SHININESS,shininess);
    OGL_DEBUG();
  }
  
  MATERIAL::MATERIAL():light(true),shader(NULL){
    for(int i=0;i<4;i++)texture[i]=NULL;
    side=GL_FRONT_AND_BACK;
  }
  MATERIAL::~MATERIAL(){}
  void MATERIAL::bind(){
    glPushAttrib(GL_COLOR_BUFFER_BIT|GL_CURRENT_BIT|GL_ENABLE_BIT|GL_LIGHTING_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    if(light){
      glEnable(GL_LIGHTING);
      glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
      color.set(GL_FRONT_AND_BACK);
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
    if(shader)shader->bind();
    OGL_DEBUG();
    for(GLuint level=0;level<4;level++) if(texture[level]!=NULL){
	glActiveTexture(GL_TEXTURE0+level);
	OGL_DEBUG();
	texture[level]->bind();
      }
    OGL_DEBUG();
  }
  void MATERIAL::ubind(){
    for(GLuint level=0;level<4;level++) if(texture[level]!=NULL){
	glActiveTexture(GL_TEXTURE0+level);
	OGL_DEBUG();
	texture[level]->ubind();
      }
    if(shader)shader->ubind();
    glPopAttrib();
  }
  
}
