/***************************************************************************
 *            camera.cpp
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
#include"camera.hxx"

namespace unobj{
  using namespace unbase;
  using namespace unmath;
  using namespace undata;
  using namespace unogl;
  using namespace unvis;

  CAMERA::CAMERA():OBJECT(),selection(false){
    aspx=vec2(-1.0,1.0);
    aspy=vec2(-1.0,1.0);
    aspz=vec2(-1.0,1.0);
    aspf=vec2(100.0,1.0);
    type=CAMERA::ortho;
  }
  CAMERA::~CAMERA(){}
  void CAMERA::ProjCalc(){
    switch(type){ // задаем перспективу
    case frust:  prjmatrix.frustum(aspx,aspy,aspz);   break;
    case ortho:  prjmatrix.ortho(aspx,aspy,aspz);     break;
    case persp:  prjmatrix.persp(aspf.x,aspf.y,aspz); break;
    case lookat: prjmatrix.lookat(eye,center,up);     break;
    }
  }

  void CAMERA::bind(){
    ProjCalc();

    glMatrixMode(GL_PROJECTION);

    glMultMatrixf(prjmatrix);
    OGL_DEBUG();

    gl_CameraPosition()=pos;
    gl_CameraRotation()=rot;

    mat4 mtr(rot);
    gl_RotateProjectionMatrix()=mtr;
    gl_RotateProjectionMatrixInv()=mtr.inv();
    mat4 mtp(pos);
    gl_TranslateProjectionMatrix()=mtp;
    gl_TranslateProjectionMatrixInv()=mtp.inv();
    mat4 mtx=mtp*mtr;
    mat4 mtxinv=mtx.inv();
    glMultMatrixf(mtxinv);
    OGL_DEBUG();

    // Calc eye plane
    mat4 pm;
    glGetFloatv(GL_PROJECTION_MATRIX,pm);
    plane[0]=vec3(-1.0,-1.0,-1.0)*pm;
    plane[1]=vec3( 1.0,-1.0,-1.0)*pm;
    plane[2]=vec3(-1.0, 1.0,-1.0)*pm;
    plane[3]=vec3( 1.0, 1.0,-1.0)*pm;

    glMatrixMode(GL_MODELVIEW);
  }

  void CAMERA::ubind(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  }

#define lsize 0.0006
#define ldir axlen.x*2
#define lsep -0.0011

  void CAMERA::draw_model(){
    /*
      glBegin(GL_TRIANGLE_STRIP);
      glVertex3fv(plane[1]);
      glVertex3fv(plane[3]);
      glVertex3fv(plane[0]);
      glVertex3fv(plane[2]);
      glEnd();
    */
    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glColor4f(1.0,1.0,1.0,1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    // Camera frame
    glVertex3f(-lsize, lsize, lsep);
    glVertex3f( lsize, lsize, lsep);
    glVertex3f( lsize, lsize, lsep);
    glVertex3f( lsize,-lsize, lsep);
    glVertex3f( lsize,-lsize, lsep);
    glVertex3f(-lsize,-lsize, lsep);
    glVertex3f(-lsize,-lsize, lsep);
    glVertex3f(-lsize, lsize, lsep);
    // Camera area
    glVertex3f(   0.0,   0.0,  0.0);
    glVertex3f( lsize, lsize, lsep);
    glVertex3f(   0.0,   0.0,  0.0);
    glVertex3f( lsize,-lsize, lsep);
    glVertex3f(   0.0,   0.0,  0.0);
    glVertex3f(-lsize,-lsize, lsep);
    glVertex3f(   0.0,   0.0,  0.0);
    glVertex3f(-lsize, lsize, lsep);
    // Camera vector
    //glVertex3f(   0.0,   0.0,   0.0);
    //glVertex3f(   0.0,   0.0, -ldir);
    // Arrow
    //glVertex3f( 0.0,     0.0, -ldir         );
    //glVertex3f( 0.0, axend.y, -ldir+axend.x );
    //glVertex3f( 0.0,     0.0, -ldir         );
    //glVertex3f( 0.0,-axend.y, -ldir+axend.x );
    glEnd();
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHTING);
  }
  CAMERA::operator string(){
    return string("CAMERA{}");
  }
  
  //*  SELECTOR  *//
  SELECTOR::SELECTOR():OBJECT(),enable(false){}
  SELECTOR::~SELECTOR(){}
  void SELECTOR::bind(){
    glSelectBuffer(NAMES_BUFFER_SIZE,_buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    BindLoc();
  }
  void SELECTOR::BindLoc(){
    GLint rendermode;
    glGetIntegerv(GL_RENDER_MODE,&rendermode);
    if(rendermode==GL_SELECT){
      GLint viewport[4];
      glGetIntegerv(GL_VIEWPORT, viewport);
      vec2 cur=glfGL2W(vec2(pos),vec2(viewport[2],viewport[3]));
      cur.y=viewport[3]-cur.y;
      vec2 del=vec2(4.0,4.0);
      glMatrixMode(GL_PROJECTION);
      gluPickMatrix((GLdouble)cur.x,(GLdouble)cur.y,(GLdouble)del.x,(GLdouble)del.y,viewport);
    }
  }
  void SELECTOR::uBindLoc(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  }
  void SELECTOR::ubind(){
    glFlush();
    _hits=glRenderMode(GL_RENDER);
    uBindLoc();
    GLuint i,j;
    GLuint *ptr;
    ptr=(GLuint*)_buffer;
    for(i=0; i<_hits; i++){
      _select[i].size=*ptr;
      ptr++;    _select[i].z.x=(scalar)*ptr/0x7fffffff;
      ptr++;    _select[i].z.y=(scalar)*ptr/0x7fffffff;
      ptr++;    //_select[i].name=new GLuint[_select[i].size];
      for(j=0; j<_select[i].size; j++){
	//printf("Hits: %d Hit: %d level: %d Name:%d\n",_hits,i,j,*ptr);
	if(*ptr!=0)_select[i].name=*ptr; ptr++;
      }
    }
  }
  GLuint SELECTOR::top()const{ // Возврат имени самого ближнего объекта
    vec2 d=vec2(100.0,100.0);
    GLuint top=0;
    for(GLuint i=0; i<_hits; i++){
      const vec2& t=_select[i].z;
      if(t[0]<d[0] || t[1]<d[1]){
	d=t;
	top=_select[i].name;
      }
    }
    return top;
  }
  
  CAMGROUP::CAMGROUP(){}
  CAMGROUP::~CAMGROUP(){}
  
  CAMGROUP::operator string(){
    return "CAMGROUP{}";
  }
  
  __GROUP_IMPLEMENTATION_(unobj::CAMGROUP,
			  unobj::CAMERA,
			  ,
			  ,
			  );
  
}
