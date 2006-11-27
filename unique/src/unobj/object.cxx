/***************************************************************************
 *            object.cpp
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

#include"object.hxx"
#include"camera.hxx"
#include"light.hxx"
#include"scene.hxx"

namespace unobj{
  using namespace unbase;
  using namespace unmath;
  using namespace undata;
  using namespace unogl;
  using namespace unvis;

  OBJECT::OBJECT():parent(NULL),target(NULL),mat(false),scene(NULL),
		   pos(vec3::null),rot(quat::id),visible(true),
		   rtype(RENDERTYPE::normal),oshadow(false),shadow(false),
		   locate(NULL),showaxis(false){
    glGenNames(1,&id);
    OGL_DEBUG();
    glGenQueries(1,&qid);
    OGL_DEBUG();
  
    axlen=0.2*vec3::one;
    axend=vec2(0.04,0.01);

    sel=false;
    act=false;
  }
  OBJECT::~OBJECT(){
    glDeleteNames(1,&id);
    OGL_DEBUG();
    glDeleteQueries(1,&qid);
    OGL_DEBUG();
  }
  bool OBJECT::update(){
    omtx=mtx;
    mtx=locatematrix();
    vel=(mtx-omtx)*vec3::null;
  }
  void OBJECT::BindName(GLenum mode){
    if(mode & RENDERMODE::name)glLoadName(id);
    OGL_DEBUG();
  }
  void OBJECT::uBindName(GLenum mode){
    if(mode & RENDERMODE::name)glLoadName(0);
    OGL_DEBUG();
  }
  void OBJECT::BindQuery(GLenum mode){
    if(mode & RENDERMODE::quer)glBeginQuery(GL_SAMPLES_PASSED,qid); // Начинаем запрос на проверку видимости
    OGL_DEBUG();
  }
  void OBJECT::uBindQuery(GLenum mode){
    if(mode & RENDERMODE::quer){
      glEndQuery(GL_SAMPLES_PASSED);// Заканчиваем запрос
      glGetQueryObjectuiv(qid,GL_QUERY_RESULT,&num_frag);// Собираем результаты
    }
    OGL_DEBUG();
  }
  GLuint OBJECT::QueryFrag()const{
    return num_frag;
  }
  void OBJECT::BindLoc(){ // Переход в локальные координаты объекта
    glMatrixMode(GL_MODELVIEW); // Переключаемся в модельную матрицу
    glPushMatrix();
    OGL_DEBUG();
    glMultMatrixf(mtx);
    OGL_DEBUG();
  }
  void OBJECT::uBindLoc(){
    glMatrixMode(GL_MODELVIEW); // Переключаемся в модельную матрицу
    glPopMatrix();
    OGL_DEBUG();
  }
  const mat4 OBJECT::matrix()const{
    return mat4(pos)*mat4(rot);
  }
  const mat4 OBJECT::locatematrix()const{
    if(locate)return locate->locatematrix()*matrix();
    else return matrix();
  }
  void OBJECT::BindMat(GLenum mode){
    if(!(mode & RENDERMODE::matl))return;
    string k; MATERIAL* m;
    mat(k,m);
    if(m)m->bind();
  }
  void OBJECT::BindMat(GLenum mode,string name){
    if(!(mode & RENDERMODE::matl))return;
    MATERIAL* m=mat.get(name);
    if(m)m->bind();
  }
  void OBJECT::uBindMat(GLenum mode){
    if(!(mode & RENDERMODE::matl))return;
    string k; MATERIAL* m;
    mat(k,m);
    if(m)m->bind();
  }
  void OBJECT::uBindMat(GLenum mode,string name){
    if(!(mode & RENDERMODE::matl))return;
    MATERIAL* m=mat.get(name);
    if(m)m->bind();
  }
  
  void OBJECT::drawaxis(GLenum mode){
    if(mode & RENDERMODE::axis){
      glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);

      glDisable(GL_DEPTH_TEST);
      glDisable(GL_LIGHTING);
      glDisable(GL_BLEND);
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
      //glDisable(GL_TEXTURE_CUBE);
      //glDepthFunc(GL_NEVER);//GL_NEVER GL_NOTEQUAL GL_ALWAYS GL_LEQUAL GL_EQUAL GL_GEQUAL GL_GREATER
      //glDepthRange( 1.0,-1.0);
      glLineWidth(1.0);
      glBegin(GL_LINES);
      // Оси
      glColor4f(1.0,0.0,0.0,1.0);
      glVertex3f(     0.0,     0.0,     0.0 ); // X
      glVertex3f( axlen.x,     0.0,     0.0 );
      glColor4f(0.0,1.0,0.0,1.0);
      glVertex3f(     0.0,     0.0,     0.0 ); // Y
      glVertex3f(     0.0, axlen.y,     0.0 );
      glColor4f(0.0,0.0,1.0,1.0);
      glVertex3f(     0.0,     0.0,     0.0 ); // Z
      glVertex3f(     0.0,     0.0, axlen.z );
      // Стрелки
      glColor4f(1.0,0.0,0.0,1.0);
      glVertex3f( axlen.x,                     0.0,             0.0 ); // X
      glVertex3f( axlen.x-axend.x,         axend.y,             0.0 );
      glVertex3f( axlen.x,                     0.0,             0.0 );
      glVertex3f( axlen.x-axend.x,        -axend.y,             0.0 );
      glColor4f(0.0,1.0,0.0,1.0);
      glVertex3f(             0.0, axlen.y,                     0.0 ); // Y
      glVertex3f(             0.0, axlen.y-axend.x,         axend.y );
      glVertex3f(             0.0, axlen.y,                     0.0 );
      glVertex3f(             0.0, axlen.y-axend.x,        -axend.y );
      glColor4f(0.0,0.0,1.0,1.0);
      glVertex3f(             0.0,             0.0, axlen.z         ); // Z
      glVertex3f(             0.0,         axend.y, axlen.z-axend.x );
      glVertex3f(             0.0,             0.0, axlen.z         );
      glVertex3f(             0.0,        -axend.y, axlen.z-axend.x );
      glEnd();

      glPopAttrib();
    }
    OGL_DEBUG();
  }

  void OBJECT::drawmodel(GLenum mode){
  
  }

  void OBJECT::casteshadow(const vec3& light_pos){
  
  }

  /* Generic DRAW */
  /*
    BindLoc();
    BindMat(mode);
    BindName(mode);
    BindQuery(mode);
    // Draw Code
    uBindName(mode);
    uBindMat(mode);
    DrawAxis(mode);
    uBindLoc();
  */
  void OBJECT::draw(GLenum mode){
    if(!visible)return;
    BindLoc();
    BindName(mode);
    BindMat(mode);
    BindQuery(mode);
    /*glColor4f(1.0,1.0,1.0,1.0);
      glBegin(GL_TRIANGLES);
      glColor4f(1.0,0.0,0.0,1.0);
      glVertex4f(-0.6, 0.6,0.0,1.0);
      glColor4f(0.0,1.0,0.0,1.0);
      glVertex4f( 0.6, 0.6,0.0,1.0);
      glColor4f(0.0,0.0,1.0,1.0);
      glVertex4f( 0.0,-0.6,0.0,1.0);
      glEnd();*/
    uBindQuery(mode);
    uBindMat(mode);
    uBindName(mode);
    drawaxis(mode);
    drawmodel(mode);
    uBindLoc();
  }

  void OBJECT::select(GLuint i){
    sel=i==id;
  }
  void OBJECT::step(TIME&time){
    update();
    stepHandler(time);
  }

  void OBJECT::event(GRAPHCONTEXT& e){
    eventHandler(e);
  }
}

#include "toluaxx.h"
namespace unobj{
  void OBJECT::stepHandler(TIME&event){
    tolua_callmethod(OBJECT,stephandle,
		     tolua_pushusertype(L,&event,"TIME"),
		     0,);
  }
  void OBJECT::drawHandler(GLenum event){
    tolua_callmethod(OBJECT,drawhandle,
		     tolua_pushnumber(L,event),
		     0,);
  }
  void OBJECT::eventHandler(GRAPHCONTEXT& event){
    tolua_callmethod(OBJECT,eventhandle,
		     tolua_pushusertype(L,&event,"CONTEXT"),
		     0,);
  }
  OBJECT::operator string(){
    return "OBJECT{}";
  }

  GROUP::GROUP():autoload(true){}
  GROUP::GROUP(bool al):autoload(al){}
  GROUP::~GROUP(){}
  void GROUP::draw(unsigned int mode){
    OBJECT::draw(mode);
    for(ITER i=pool.begin();i!=pool.end();i++)i->second->draw(mode);
  }
  void GROUP::casteshadow(const vec3& lp){
    for(ITER i=pool.begin();i!=pool.end();i++)i->second->casteshadow(lp);
  }
  void GROUP::step(TIME&t){
    OBJECT::step(t);
    for(ITER i=pool.begin();i!=pool.end();i++)i->second->step(t);
  }
  void GROUP::select(unsigned int e){
    OBJECT::select(e);
    for(ITER i=pool.begin();i!=pool.end();i++)i->second->select(e);
  }
  void GROUP::event(GRAPHCONTEXT& e){
    OBJECT::event(e);
    for(ITER i=pool.begin();i!=pool.end();i++)i->second->event(e);
  }
  GROUP::operator string(){
    string r="{";
    for(ITER i=pool.begin();i!=pool.end();i++){r+=i->first+",";}
    if(r[r.length()-1]==',')r[r.length()-1]='}';else r+="}";
    return string("GROUP{child=")+r+"}";
  }
  __GROUP_IMPLEMENTATION_(unobj::GROUP,
			  unobj::OBJECT,
			  object,
			  "return unobj.GROUP()",
			  "local GROUP =unobj.GROUP \n"
			  "local OBJECT=unobj.OBJECT\n"
			  "local CAMERA=unobj.CAMERA\n"
			  "local LIGHT =unobj.LIGHT \n",
			  o->scene=scene,
			  o->scene=NULL);  
}
