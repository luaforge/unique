/***************************************************************************
 *            geometry.hpp
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
#include"unobj.hxx"

namespace ungeom{//tolua_export
  /*
   *  Geometry plane
   */
  class PLANE: public unobj::OBJECT{//tolua_export
  protected:
    vec3 ocenter;
    vec2 osize;
    vec3 b,e;
  public:
    //tolua_begin
    /*  
	GLuint polig; // Num of poligones
	vec3* texcrd; // Texture coords
	vec3* vertex; // Vertexes
	vec3* normal; // Normals
    */
    vec2 size;  // Box size
    vec3 center;// Center coordinates of the box

    PLANE();
    virtual ~PLANE();
    
    void draw_geom(class unobj::MODE&); // Renderering
    bool update();

    operator string();
    //tolua_end
  };//tolua_export

  /*
   *  Geometry box
   */
  class BOX: public unobj::OBJECT{//tolua_export
  protected:
    vec3 osize,ocenter;
    vec3 b,e;
  public:
    //tolua_begin
    /*  
	GLuint polig; // Num of poligones
	vec3* texcrd; // Texture coords
	vec3* vertex; // Vertexes
	vec3* normal; // Normals
    */
    vec3 size;  // Box size
    vec3 center;// Center coordinates of the box
  
    BOX();
    virtual ~BOX();
 
    void draw_geom(const unobj::MODE&); // Renderering
    bool update();
  
    operator string();
    //tolua_end
  };//tolua_export

  /*
   *  Geometry sphere
   */
  class SPHERE: public unobj::OBJECT{//tolua_export
  public:
    //tolua_begin
    vec2 segment;
    vec3 center;
    scalar radius;
  
    SPHERE();
    virtual ~SPHERE();
    
    void draw_geom(const unobj::MODE&); // Renderering  
    bool update();
  
    operator string();
    //tolua_end
  };//tolua_export

  //class CILYNDER;
}//tolua_export
