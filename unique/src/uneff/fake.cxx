/***************************************************************************
 *            fake.cpp
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

#include"fake.hxx"

namespace uneff{
  using namespace unogl;
  
  FAKE::FAKE():OBJECT(),size(0.1,0.1){}
  FAKE::~FAKE(){}
  
  void FAKE::bind_location(){
    glPushMatrix();
    mat4 trnmtx,posmtx; posmtx.translate(pos);
    if(target)trnmtx.translate(target->pos);
    trnmtx*=posmtx;
    glMultMatrixf(trnmtx);
    glMultMatrixf(unogl::gl_RotateProjectionMatrix());
  }

  void FAKE::draw_geom(){
    glShadeModel(GL_SMOOTH);
    //  glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
    OGL_DEBUG();
    vec2 half=size*0.5;
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glMultiTexCoord2f(0,0.0,0.0); glVertex2f(-half.x,-half.y);
    glMultiTexCoord2f(0,0.0,1.0); glVertex2f( half.x,-half.y);
    glMultiTexCoord2f(0,1.0,1.0); glVertex2f( half.x, half.y);
    glMultiTexCoord2f(0,1.0,0.0); glVertex2f(-half.x, half.y);
    glEnd();
    OGL_DEBUG();
  }
  
  FAKE::operator string(){
    return string("FAKE()");
  }
}
