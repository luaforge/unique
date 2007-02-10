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

#if 0
#define OBJECT_DEBUG(m) {cout<<m<<endl;}
#else
#define OBJECT_DEBUG(m)
#endif

namespace unobj{
  using namespace unbase;
  using namespace unmath;
  using namespace undata;
  using namespace unogl;
  using namespace unvis;

  OBJECT::OBJECT():parent(NULL),target(NULL),locate(NULL),
		   mat(NULL),scene(NULL),render(NULL),
		   pos(vec3::null),rot(quat::id),
		   select(false),active(false){
    glGenNames(1,&id);
    OGL_DEBUG();
    glGenQueries(1,&qid);
    OGL_DEBUG();
  
    axlen=0.2*vec3::one;
    axend=vec2(0.04,0.01);
  }
  OBJECT::~OBJECT(){
    glDeleteNames(1,&id);
    OGL_DEBUG();
    glDeleteQueries(1,&qid);
    OGL_DEBUG();
    cout<<">>> delete object: "<<name<<endl;
  }
  bool OBJECT::update(){
    omtx=mtx;
    mtx=locatematrix();
    vel=(mtx-omtx)*vec3::null;
  }
  void OBJECT::bind_name(){
    glLoadName(id);
    OGL_DEBUG();
  }
  void OBJECT::ubind_name(){
    glLoadName(0);
    OGL_DEBUG();
  }
  void OBJECT::bind_query(){
    glBeginQuery(GL_SAMPLES_PASSED,qid);// Occlusion query
    OGL_DEBUG();
  }
  void OBJECT::ubind_query(){
    glEndQuery(GL_SAMPLES_PASSED);// Occlusion query
    glGetQueryObjectuiv(qid,GL_QUERY_RESULT,&fragments);
    OGL_DEBUG();
  }
  void OBJECT::bind_loc(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    OGL_DEBUG();
    glMultMatrixf(mtx);
    OGL_DEBUG();
  }
  void OBJECT::ubind_loc(){
    glMatrixMode(GL_MODELVIEW);
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
  void OBJECT::bind_mat(){
    if(mat)mat->bind();
  }
  void OBJECT::ubind_mat(){
    if(mat)mat->ubind();
  }
  
  void OBJECT::draw_axis(){
    glPushAttrib(GL_COLOR_BUFFER_BIT|GL_CURRENT_BIT|GL_ENABLE_BIT|GL_LIGHTING_BIT);
    
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
    // Axis lines
    glColor4f(1.0,0.0,0.0,1.0);
    glVertex3f(     0.0,     0.0,     0.0 ); // X
    glVertex3f( axlen.x,     0.0,     0.0 );
    glColor4f(0.0,1.0,0.0,1.0);
    glVertex3f(     0.0,     0.0,     0.0 ); // Y
    glVertex3f(     0.0, axlen.y,     0.0 );
    glColor4f(0.0,0.0,1.0,1.0);
    glVertex3f(     0.0,     0.0,     0.0 ); // Z
    glVertex3f(     0.0,     0.0, axlen.z );
    // Axis vectors
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
    OGL_DEBUG();
  }
  
  void OBJECT::draw_model(){
    glColor4f(1.0,1.0,1.0,1.0);
    glBegin(GL_TRIANGLES);
    glColor4f(1.0,0.0,0.0,1.0);
    glVertex4f(-0.6, 0.6,0.0,1.0);
    glColor4f(0.0,1.0,0.0,1.0);
    glVertex4f( 0.6, 0.6,0.0,1.0);
    glColor4f(0.0,0.0,1.0,1.0);
    glVertex4f( 0.0,-0.6,0.0,1.0);
    glEnd();
  }

  void OBJECT::draw_geom(const unobj::MODE&m){
    /* no body */
  }
  
  void OBJECT::draw(const unobj::MODE&m){
    bind_loc();
    
    if(m.name)bind_name();
    //if(m.matl)bind_mat();
    if(m.quer)bind_query();
    
    draw_handler(m);
    
    if(m.geom)draw_geom(m);
    
    if(m.name)ubind_name();
    //if(m.matl)ubind_mat();
    if(m.quer)ubind_query();
    
    if(m.axis)draw_axis();
    if(m.modl)draw_model();
    
    ubind_loc();
  }
  void OBJECT::step(const unbase::TIME&t){
    step_handler(t);
  }
  void OBJECT::event(unogl::GRAPHCONTEXT&e){
    event_handler(e);
  }
}

#include"toluaxx.h"
namespace unobj{
  void OBJECT::step_handler(const unbase::TIME&t){
    tolua_callmethod(unobj::OBJECT,stephandle,
		     tolua_pushusertype(L,(void*)&t,"unbase::TIME"),
		     0,);
  }
  void OBJECT::draw_handler(const unobj::MODE&m){
    tolua_callmethod(unobj::OBJECT,drawhandle,
		     tolua_pushusertype(L,(void*)&m,"unobj::MODE"),
		     0,);
  }
  void OBJECT::event_handler(unogl::GRAPHCONTEXT&e){
    tolua_callmethod(unobj::OBJECT,eventhandle,
		     tolua_pushusertype(L,&e,"unogl::GRAPHCONTEXT"),
		     0,);
  }
  OBJECT::operator string(){
    return "OBJECT{}";
  }

  GROUP::GROUP():OBJECT(){}
  GROUP::~GROUP(){
    cout<<">>> delete group: "<<name<<endl;
    //pool.clear();
  }
  
  void GROUP::step(const unbase::TIME&t){
    OBJECT::step(t);
    for(ITER i=begin();i!=end();i++){
      i->second->step(t);
      OBJECT_DEBUG("step object: "<<i->first);
    }
  }
  void GROUP::event(unogl::GRAPHCONTEXT&e){
    OBJECT::event(e);
    for(ITER i=begin();i!=end();i++){
      i->second->event(e);
      OBJECT_DEBUG("event object: "<<i->first);
    }
  }
  GROUP::operator string(){
    string r="{";
    for(ITER i=begin();i!=end();i++){r+=i->first+"="+static_cast<string>(*(i->second))+",";}
    if(r[r.length()-1]==',')r[r.length()-1]='}';else r+="}";
    return string("GROUP{")+r+"}";
  }
  int GROUP::operator~(){
    return pool.size();
  }
  
  __GROUP_IMPLEMENTATION_(unobj::GROUP,
			  unobj::OBJECT,
			  if(scene && scene->autoload){
			    __GROUP_HIER_TRY_GET_CXXCODE_(unobj::GROUP,
							  unobj::OBJECT,
							  object,
							  "return unobj.GROUP(true)",
							  "local GROUP =unobj.GROUP \n"
							  "local OBJECT=unobj.OBJECT\n"
							  "local CAMERA=unobj.CAMERA\n"
							  "local LIGHT =unobj.LIGHT \n"
							  "local MESH  =ungeom.MESH \n"
							  "local HMAP  =ungeom.HMAP \n"
							  "local FAKE  =uneff.FAKE  \n"
							  "local PARTICLE=uneff.PARTICLE\n"
							  )
			      },
			  __GROUP_HIER_SET_CXXCODE_(o->scene=scene;
						    CAMERA* c=dynamic_cast<CAMERA*>(o);
						    if(c)scene->camera.set(o->name,c);
						    LIGHT* l=dynamic_cast<LIGHT*>(o);
						    if(l)scene->light.set(o->name,l);
						    ),
			  __GROUP_HIER_DEL_CXXCODE_(CAMERA* c=dynamic_cast<CAMERA*>(o);
						    if(c)scene->camera.set(o->name,NULL);
						    LIGHT* l=dynamic_cast<LIGHT*>(o);
						    if(l)scene->light.set(o->name,NULL);
						    o->scene=NULL;
						    )
			  );
  
}
