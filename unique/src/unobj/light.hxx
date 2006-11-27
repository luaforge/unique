/***************************************************************************
 *            light.hpp
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
  class LIGHT: public OBJECT{//tolua_export
  public:
    //tolua_begin
    enum TYPE{
      DIR=0x1, // Directional
      POS=0x2, // Positional
    };
    //tolua_end
  protected:
    TYPE otype;
  public:
    //tolua_begin
    static unsigned int limit; // Max light sources per scene
    static unmath::vec4 globalambient;
    //static unsigned int rendtype;
    unsigned int prior;
    
    // Light colors
    unmath::vec4  ambient;        // Ambient color
    unmath::vec4  diffuse;        // Diffuse color
    unmath::vec4  specular;       // Specular color
    unmath::vec4  position;       // Source position
    // Light spot parameters
    unmath::vec4  halfVector;     // 
    unmath::vec3  spotDirection;  // Spot direction
    float spotExponent;   // Spot concentration
    float spotCutoff;     // Cut off [0.0,90.0], 180.0
    float spotCosCutoff;  // cos(spotCutoff)
    // Light attenuation
    float constatten; // Constant attenuation
    float linatten;   // Linear attenuation
    float quadatten;  // Quadratic attenuation
    // Light modes
    TYPE type;   // Source type
    unvis::SHADER* shader;
  
    LIGHT();
    virtual ~LIGHT();
    operator string();
    void bind();
    void ubind();
    void draw(unsigned int mode=RENDERMODE::imad);
    bool update();
    //tolua_end
  };//tolua_export
  
  class LHTGROUP{//tolua_export
  public:
    typedef map<string,LIGHT*>::iterator ITER;
  protected:
    typedef map<string,LIGHT*> POOL;
    typedef multimap<scalar,LIGHT*> PRIOR;
    typedef multimap<scalar,LIGHT*>::iterator PITER;
    POOL pool;
  public:
    PRIOR lp;
    ITER begin();
    ITER end();
    //tolua_begin
    LHTGROUP();
    virtual ~LHTGROUP();
    void operator()(string&/** k="" asnil**/,LIGHT*&);
    /**tolua_getindex {**/
    LIGHT* get(string);
    /**}**/
    /**tolua_setindex {**/
    void set(string,LIGHT*);
    /**}**/
    operator string();
    void bind();
    void ubind();
    bool update();
    //tolua_end
  };//tolua_export
  
}//tolua_export
