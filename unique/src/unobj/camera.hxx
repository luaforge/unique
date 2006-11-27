/***************************************************************************
 *            camera.hpp
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

#pragma once
#include"object.hxx"

namespace unobj{//tolua_export
#define NAMES_BUFFER_SIZE 1024
  class SELECTOR: public OBJECT{//tolua_export
  public:
    //tolua_begin
    struct SELECT{
      unsigned int size; // Stack selection size
      unsigned int name; // Names array
      unmath::vec2 z;    // Depth range
    };
    //tolua_end
  protected:
    SELECT _select[NAMES_BUFFER_SIZE];
    GLuint _buffer[NAMES_BUFFER_SIZE];
    GLint  _hits;
    GLuint _top;
  public:
    //tolua_begin
    bool enable;
    SELECTOR();
    ~SELECTOR();
    void bind();
    void ubind();
    unsigned int top()const; // Возврат имени самого ближнего объекта
    //tolua_end
    void BindLoc();
    void uBindLoc();
  };//tolua_export
  
# define SIMPLE_CAMERA

  class CAMERA: public OBJECT{//tolua_export
  public:
    //tolua_begin
    enum {
      ortho=0x1,
      persp=0x2,
      frust=0x4,
      lookat=0x3,
    };
    
    unsigned int type;
    unmath::mat4 prjmatrix;
    
    unmath::vec3 eye;
    unmath::vec3 center;
    unmath::vec3 up;
    // for frustum
    unmath::vec2 aspx;// left right
    unmath::vec2 aspy;// bottom top
    unmath::vec2 aspz;// near far
    // for perspective
    unmath::vec2 aspf;// fovx/fovy
    unogl::GRAPHCONTEXT* context;
    unsigned int layer;
    SELECTOR pointer;
    bool selection;
    unmath::vec3 plane[4];

    CAMERA();
    virtual ~CAMERA();
    void bind();
    void ubind();
    void draw(unsigned int mode=RENDERMODE::imad);
    operator string();
    //tolua_end
    void ProjCalc();
  };//tolua_export

  class CAMGROUP{//tolua_export
  public:
    typedef map<string,CAMERA*>::iterator ITER;
  protected:
    typedef map<string,CAMERA*> POOL;
    POOL pool;
  public:
    ITER begin();
    ITER end();
    //tolua_begin
    CAMGROUP();
    virtual ~CAMGROUP();
    void operator()(string&/** k="" asnil**/,CAMERA*&);
    /**tolua_getindex {**/
    CAMERA* get(string);
    /**}**/
    /**tolua_setindex {**/
    void set(string,CAMERA*);
    /**}**/
    operator string();
    /*
    void bind();
    void ubind();
    bool update();
    */
    //tolua_end
  };//tolua_export
}//tolua_export
