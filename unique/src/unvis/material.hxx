/***************************************************************************
 *            material.hpp
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
#include "unbase.hxx"
#include "unmath.hxx"
#include "unogl.hxx"
#include "texture.hxx"
#include "shader.hxx"

// The OpenGL(R) Shading Language  v1.051

namespace unvis{//tolua_export

  class MATGROUP;
  class MATERIAL{//tolua_export
  public:
    class COLOR{//tolua_export
    public:
      //tolua_begin
      unmath::vec4 emission;
      unmath::vec4 ambient;
      unmath::vec4 diffuse;
      unmath::vec4 specular;
      scalar shininess;
      //tolua_end
      COLOR();
      void set(unsigned int);
    };//tolua_export
    
    //tolua_begin
    /**tolua_readonly**/ MATGROUP* parent;
    /**tolua_readonly**/ string name;
    bool light;
    /**tolua_readonly**/ COLOR  color;
    unsigned int side;
    TEXTURE* texture[8];
    SHADERPROG* shader;
  
    MATERIAL();
    virtual ~MATERIAL();
    void bind();
    void ubind();
    //tolua_end
  };//tolua_export
  
  class MATGROUP: public MATERIAL{//tolua_export
  protected:
    typedef map<string,MATERIAL*> CONT;
    typedef map<string,MATERIAL*>::iterator ITER;
    CONT array;
    string hiername(string n="");
  public:
    //tolua_begin
    MATGROUP();
    ~MATGROUP();
    void operator()(string&/** k="" asnil**/,MATERIAL*&);
    /**tolua_getindex {**/
    MATERIAL* get(string);
    /**}**/
    /**tolua_setindex {**/
    void set(string,MATERIAL*);
    /**}**/
    operator string();
    //tolua_end
  };//tolua_export
  
}//tolua_export

