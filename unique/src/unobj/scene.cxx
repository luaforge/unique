/***************************************************************************
 *            scene.cpp
 *
 *  Wed Jun 29 17:11:31 2005
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

#include"scene.hxx"

namespace unobj{
  
  SCENE::SCENE():eventer(NULL),autoload(true),object(),camera(),light(),material(true),texture(true),shader(true){
    object.scene=this;
  }
  SCENE::~SCENE(){
    cout<<"delete scene: my "<<endl;
  }
  
  void SCENE::draw(const unobj::MODE&mode){
    /*
    glEnable(GL_DEPTH_TEST);
    
    light.bind();
    
    //cout<<"Begin draw"<<endl;
    for(GROUP::ITER i=object.begin();i!=object.end();i++){
      OBJECT* oo=(*i).second;
      //if(oo->mat.blend){
	cout<<"Draw normal "<<(*i).first<<endl;
	oo->draw(mode);
	//}
    }
    
    vec3 dir=unogl::gl_RotateProjectionMatrix()*vec3::pz;
    
    //glDepthMask(GL_FALSE);
    deque<OBJECT*> objs;
    for(GROUP::ITER i=object.begin();i!=object.end();i++){
      OBJECT* oo=(*i).second;
      if(oo->mat.blend){
	bool inserted=false;
	scalar od=oo->pos*dir;
	//scalar od=(co->pos-oo->pos).len();
	for(deque<OBJECT*>::iterator in=objs.begin();in!=objs.end();in++){
	  scalar zd=(*in)->pos*dir;
	  //scalar zd=(co->pos-(*in)->pos).len();
	  if(od>zd){
	    //if(in==objs.begin())objs.push_front(oo);else objs.insert(in-1,oo);
	    objs.insert(in,oo);
	    inserted=true;
	    break;
	  }
	}
	if(!inserted)objs.push_back(oo);
      }
    }
  
    for(LHTGROUP::ITER l=light.begin();l!=light.end();l++){
      LIGHT* lo=(LIGHT*)(*l).second;
      if(lo->shadow)drawshadow(*lo);
    }
  
    for(deque<OBJECT*>::iterator id=objs.begin();id!=objs.end();id++){
      cout<<"Draw blend "<<(*id)->name<<endl;
      (*id)->draw(mode);
    }
    glDepthMask(GL_TRUE);
    light.ubind();

    //  co->ubind();
    //}
    //cout<<"End draw"<<endl;
    */
  }

  void SCENE::drawshadow(const LIGHT& l){
    /*
    vec3 lpos=l.locatematrix()*vec3();
    unsigned int mean_count=0;
    vec4 mean_intensity(vec4::null);
    for(LHTGROUP::ITER li=light.begin();li!=light.end();li++){
      LIGHT* lo=(LIGHT*)(*li).second;
      if(lo!=&l){
	mean_intensity+=lo->diffuse;
	mean_count++;
      }
    }
    if(mean_count>0)mean_intensity*=oo_scalar(mean_count);
    vec4 ov4=vec4::one;
    vec4 shadecolor=ov4-(LIGHT::globalambient+mean_intensity);
    //vec4 shadecolor=vec4(0.0,0.0,0.0,0.7);
    //cout<<"shadecolor:"<<shadecolor<<" ambient:"<<LIGHT::globalambient<<","<<mean_intensity<<endl;

    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT |
		 GL_POLYGON_BIT      | GL_STENCIL_BUFFER_BIT);
    glClear(GL_STENCIL_BUFFER_BIT);
    glPolygonMode(GL_FRONT,GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glLineWidth(3.0);
    //glPointSize(0.0f);
    glDisable(GL_POLYGON_SMOOTH);
    glEdgeFlag(GL_TRUE);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_STENCIL_TEST);
    glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
    glStencilFunc(GL_ALWAYS,1,0xFFFFFFFF);
    // Caste all shadows
    for(GROUP::ITER i=object.begin();i!=object.end();i++){
      OBJECT* oo=(*i).second;
      if(!oo->mat.blend)oo->casteshadow(lpos);
    }
    // Difference Camera plane
    mat4 pm;
    vec3 plane[4];
    glGetFloatv(GL_PROJECTION_MATRIX,pm);
    plane[0]=vec3(-1.0,-1.0,-1.0)*pm;
    plane[1]=vec3( 1.0,-1.0,-1.0)*pm;
    plane[2]=vec3(-1.0, 1.0,-1.0)*pm;
    plane[3]=vec3( 1.0, 1.0,-1.0)*pm;
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3fv(plane[1]);
    glVertex3fv(plane[3]);
    glVertex3fv(plane[0]);
    glVertex3fv(plane[2]);
    glEnd();

    // draw stencil shadow
    glFrontFace(GL_CCW);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    // draw a shadowing rectangle covering the entire screen
    glColor4fv(shadecolor);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glStencilFunc(GL_NOTEQUAL,0,0xFFFFFFFF);
    glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
  
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
  
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-1.0f, 1.0f,-0.0f);
    glVertex3f(-1.0f,-1.0f,-0.0f);
    glVertex3f( 1.0f, 1.0f,-0.0f);
    glVertex3f( 1.0f,-1.0f,-0.0f);
    glEnd();
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopAttrib();
    */
  }
  
  void SCENE::event(){
    if(eventer)object.event(*eventer);
  }
  void SCENE::step(const unbase::TIME&t){
    object.step(t);
  }
  bool SCENE::update(){
    autoload=true;
    object.update();
    material.update();
    texture.update();
    shader.update();
    autoload=false;
  }
  SCENE::operator string(){return string("SCENE(")+")";}
  
  SCNGROUP::SCNGROUP(){
    
  }
  SCNGROUP::~SCNGROUP(){
    
  }
  bool SCNGROUP::update(){
    for(ITER i=begin();i!=end();i++)i->second->update();
  }
  SCNGROUP::operator string(){
    string ret="{";
    for(ITER i=pool.begin();i!=pool.end();i++){ret+=(*i).first+",";}
    if(ret[ret.length()-1]==',')ret[ret.length()-1]='}';else ret+="}";
    return ret;
  }
  __GROUP_IMPLEMENTATION_(unobj::SCNGROUP,
			  unobj::SCENE,
			  __GROUP_TRY_GET_CXXCODE_(unobj::SCNGROUP,
						   unobj::SCENE,
						   scene,
						   "local SCENE=unobj.SCENE"
						   ),
			  cout<<"scene set"<<endl,
			  );

}
