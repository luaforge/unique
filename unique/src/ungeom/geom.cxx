/***************************************************************************
 *            geometry.cpp
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

#include"geom.hxx"

namespace ungeom{
  using namespace unogl;

  PLANE::PLANE():OBJECT(),size(vec3::one){}
  PLANE::~PLANE(){}
  void PLANE::draw_geom(class unobj::MODE&m){
    if(m.matl)bind_mat();
  
    glBegin(GL_QUADS);
    // Front
    glNormal3f(0.0,0.0,-1.0);
    ungeom::glMultiTexCoord2f(GL_TEXTURE0,0.0,0.0); ungeom::glMultiTexCoord2f(GL_TEXTURE1,0.0,0.0); glVertex3f(b.x,b.y,b.z);
    ungeom::glMultiTexCoord2f(GL_TEXTURE0,0.0,1.0); ungeom::glMultiTexCoord2f(GL_TEXTURE1,0.0,1.0); glVertex3f(e.x,b.y,b.z);
    ungeom::glMultiTexCoord2f(GL_TEXTURE0,1.0,1.0); ungeom::glMultiTexCoord2f(GL_TEXTURE1,1.0,1.0); glVertex3f(e.x,e.y,b.z);
    ungeom::glMultiTexCoord2f(GL_TEXTURE0,1.0,0.0); ungeom::glMultiTexCoord2f(GL_TEXTURE1,1.0,0.0); glVertex3f(b.x,e.y,b.z);
    glEnd();

    OGL_DEBUG();
  
    if(m.matl)ubind_mat();
  }
  bool PLANE::update(){
    vec3 n=0.5*size;
    b=(center-vec3::one)%n;
    e=(center+vec3::one)%n;
    boundbox=size;
    boundsphere=max(size.x,size.y)*0.5*pow(2.0,0.5);
    return true;
  }
  PLANE::operator string(){return string("PLANE()");}

  BOX::BOX():OBJECT(),size(vec3::one){}
  /*
      _________e
     /        /|
    /________/ |
    |        | |
  ^ |        | |
  | |        | /
    |________|/
    b
    
    y z
    |/_x

    vec3 b;
    vec3 e;

  */
  BOX::~BOX(){}
  void BOX::draw_geom(const unobj::MODE&m){
    if(m.matl)bind_mat();
  
    glBegin(GL_QUADS);
    // Front
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(b.x,b.y,b.z);
    glVertex3f(e.x,b.y,b.z);
    glVertex3f(e.x,e.y,b.z);
    glVertex3f(b.x,e.y,b.z);
    // Back
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(e.x,e.y,e.z);
    glVertex3f(e.x,b.y,e.z);
    glVertex3f(b.x,b.y,e.z);
    glVertex3f(b.x,e.y,e.z);
    // Left
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(b.x,b.y,b.z);
    glVertex3f(b.x,e.y,b.z);
    glVertex3f(b.x,e.y,e.z);
    glVertex3f(b.x,b.y,e.z);
    // Right
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(e.x,e.y,e.z);
    glVertex3f(e.x,e.y,b.z);
    glVertex3f(e.x,b.y,b.z);
    glVertex3f(e.x,b.y,e.z);
    // Top
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(e.x,e.y,e.z);
    glVertex3f(b.x,e.y,e.z);
    glVertex3f(b.x,e.y,b.z);
    glVertex3f(e.x,e.y,b.z);
    // Bottom
    glNormal3f(0.0,-1.0,0.0);
    glVertex3f(b.x,b.y,b.z);
    glVertex3f(b.x,b.y,e.z);
    glVertex3f(e.x,b.y,e.z);
    glVertex3f(e.x,b.y,b.z);
    glEnd();

    OGL_DEBUG();
  
    if(m.matl)ubind_mat();
  }
  bool BOX::update(){
    vec3 n=0.5*size;
    b=(center-vec3::one)%n;
    e=(center+vec3::one)%n;
    boundbox=size;
    boundsphere=max(max(size.x,size.y),size.z)*0.5*pow(2.0,0.5);
    return true;
  }
  BOX::operator string(){return string("BOX()");}

  SPHERE::SPHERE():OBJECT(),segment(12,12){}
  SPHERE::~SPHERE(){}
  void SPHERE::draw_geom(const unobj::MODE&m){ // Renderering
    if(m.matl)bind_mat();
    
    for(unsigned int i=0;i<-1+segment.x;i++){
      scalar t=i/(segment.x-1.f);
      scalar t2=(i+1)/(segment.x-1.f);
      scalar phi=unmath::cnst::one_pi*t-unmath::cnst::half_pi;
      scalar phi2=unmath::cnst::one_pi*t2-unmath::cnst::half_pi;
      glBegin(GL_QUAD_STRIP);
      for(unsigned int j=0;j<segment.y;j++){
	scalar s=j/(segment.x-1.f);
	scalar theta=2*unmath::cnst::one_pi*s;
	
	ungeom::glMultiTexCoord2f(GL_TEXTURE0,s,t);
	glNormal3f(cos(phi)*cos(theta),sin(phi),cos(phi)*sin(theta));
	glVertex3f(radius*cos(phi)*cos(theta),radius*sin(phi),-radius*cos(phi)*sin(theta));
	
	ungeom::glMultiTexCoord2f(GL_TEXTURE0,s,t2);
	glNormal3f(cos(phi2)*cos(theta),sin(phi2),cos(phi2)*sin(theta));
	glVertex3f(radius*cos(phi2)*cos(theta),radius*sin(phi2),-radius*cos(phi2)*sin(theta));
      }
      glEnd();
    }
    OGL_DEBUG();
    
    if(m.matl)ubind_mat();
  }
  bool SPHERE::update(){}
  SPHERE::operator string(){return "SPHERE()";}
}
