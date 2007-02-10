/***************************************************************************
 *            light.cpp
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

#include"light.hxx"

namespace unobj{
  using namespace unbase;
  using namespace unmath;
  using namespace undata;
  using namespace unogl;
  using namespace unvis;
  
  vec4 LIGHT::globalambient=vec4(0.2,0.2,0.2,1.0);
  unsigned int LIGHT::limit=4;

  LIGHT::LIGHT():OBJECT(),
		 ambient(0.8,0.8,0.8,1.0),diffuse(0.8,0.8,0.8,1.0),specular(0.8,0.8,0.8,1.0),
		 spotCutoff(180.0),spotExponent(0.0),
		 quadatten(0.0),linatten(0.0),constatten(1.0),
		 type(POS){}
  LIGHT::~LIGHT(){}

  void LIGHT::bind(){
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalambient);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);

    mat4 mtx=locatematrix();

    position=mtx*vec3::null;
    //position=pos;
    spotDirection=mat4(rot)*vec3(0.0,0.0,-1.0);

    if(type==LIGHT::DIR){
      position.w=0.0;
      position.x=-spotDirection.x;
      position.y=-spotDirection.y;
      position.z=-spotDirection.z;
    }
    if(type==LIGHT::POS){
      position.w=1.0;
    }

    glLightfv(GL_LIGHT0+prior,GL_POSITION,position);
    glLightfv(GL_LIGHT0+prior,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0+prior,GL_DIFFUSE,diffuse);
    glLightfv(GL_LIGHT0+prior,GL_SPECULAR,specular);
    OGL_DEBUG();

    glLightf (GL_LIGHT0+prior,GL_CONSTANT_ATTENUATION,constatten);
    glLightf (GL_LIGHT0+prior,GL_LINEAR_ATTENUATION,linatten);
    glLightf (GL_LIGHT0+prior,GL_QUADRATIC_ATTENUATION,quadatten);
    OGL_DEBUG();

    glLightf (GL_LIGHT0+prior,GL_SPOT_CUTOFF,spotCutoff);
    glLightfv(GL_LIGHT0+prior,GL_SPOT_DIRECTION,spotDirection);
    glLightf (GL_LIGHT0+prior,GL_SPOT_EXPONENT,spotExponent);
    OGL_DEBUG();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0+prior);
  }

  void LIGHT::ubind(){
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0+prior);
  }

  bool LIGHT::update(){
    //if(pixelshadow&&!opixelshadow){
    
    //}
    return false;
  }

#define lsize 0.04
#define ldir axlen.x*2

  void LIGHT::draw_model(){
    //glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_NEVER);//GL_NOTEQUAL GL_ALWAYS GL_LEQUAL GL_EQUAL GL_GEQUAL GL_GREATER
    glColor4f(1.0,1.0,1.0,1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    // Top tripod
    glVertex3f(-lsize,   0.0,   0.0);
    glVertex3f(   0.0, lsize,   0.0);
    
    glVertex3f(-lsize,   0.0,   0.0);
    glVertex3f(   0.0,-lsize,   0.0);
    
    glVertex3f(-lsize,   0.0,   0.0);
    glVertex3f(   0.0,   0.0, lsize);
    
    glVertex3f(-lsize,   0.0,   0.0);
    glVertex3f(   0.0,   0.0,-lsize);
    
    // Bottom tripod
    glVertex3f( lsize,   0.0,   0.0);
    glVertex3f(   0.0, lsize,   0.0);
    
    glVertex3f( lsize,   0.0,   0.0);
    glVertex3f(   0.0,-lsize,   0.0);
    
    glVertex3f( lsize,   0.0,   0.0);
    glVertex3f(   0.0,   0.0, lsize);
    
    glVertex3f( lsize,   0.0,   0.0);
    glVertex3f(   0.0,   0.0,-lsize);
    
    // Frame
    glVertex3f(   0.0, lsize,   0.0);
    glVertex3f(   0.0,   0.0, lsize);
    
    glVertex3f(   0.0,-lsize,   0.0);
    glVertex3f(   0.0,   0.0, lsize);
    
    glVertex3f(   0.0,   0.0,-lsize);
    glVertex3f(   0.0,-lsize,   0.0);
    
    glVertex3f(   0.0,   0.0,-lsize);
    glVertex3f(   0.0, lsize,   0.0);
    
    // Project vector
    glVertex3f(   0.0,   0.0,   0.0);
    glVertex3f(   0.0,   0.0, -ldir);
    // Project vector arrow
    glVertex3f( 0.0,     0.0, -ldir         );
    glVertex3f( 0.0, axend.y, -ldir+axend.x );
    glVertex3f( 0.0,     0.0, -ldir         );
    glVertex3f( 0.0,-axend.y, -ldir+axend.x );
    
    glEnd();
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHTING);
    
    OGL_DEBUG();
  }
  
  LIGHT::operator string(){
    return "LIGHT()";
  }

  LHTGROUP::LHTGROUP(){}
  LHTGROUP::~LHTGROUP(){}
  void LHTGROUP::bind(){
    update();
    unsigned int k=0;
    for(PITER j=lp.begin();k<LIGHT::limit&&j!=lp.end();j++,k++){
      j->second->prior=k;
      j->second->bind();
    }
    gl_Lights()=k;
  }
  void LHTGROUP::ubind(){
    unsigned int k=0;
    for(PITER j=lp.begin();k<LIGHT::limit&&j!=lp.end();j++,k++)j->second->ubind();
  }
  bool LHTGROUP::update(){
    vec3& cpos=gl_CameraPosition();
    quat& crot=gl_CameraRotation();
    lp.clear();
    for(ITER i=pool.begin();i!=pool.end();i++){
      LIGHT*l=i->second;
      vec3 lpos=l->locatematrix()*vec3::null;
      lp.insert(make_pair<scalar,LIGHT*>((cpos-lpos).len(),l));
    }
  }
  LHTGROUP::operator string(){
    string r="LHTGROUP(";
    for(ITER i=pool.begin();i!=pool.end();i++)r+=i->first+",";
    r.erase(r.length()-1);
    r+=")";
    return r;
  }
  
  __GROUP_IMPLEMENTATION_(unobj::LHTGROUP,
			  unobj::LIGHT,
			  ,
			  ,
			  );
  
}
