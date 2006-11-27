/***************************************************************************
 *            scene.hpp
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
#include"light.hxx"
#include"camera.hxx"

namespace unobj{//tolua_export
  class SCENE{//tolua_export
  protected:
    string osrc;
  public:
    //tolua_begin
    unogl::GRAPHCONTEXT* eventer;
    string src;
    unvis::SHDGROUP shader;   // scene shaders
    unvis::TEXGROUP texture;  // scene textures
    unvis::MATGROUP material; // scene materials
    
    unobj::CAMGROUP camera;   // scene cameras
    unobj::LHTGROUP light;    // scene light sources
    unobj::GROUP    object;   // scene objects
    //  CHILD listen;   // слушатели сцены
    //  CHILD sound;    // источники звука сцены
    //  CHILD control;  // контроллеры сцены
    //  CHILD pointer;  // главный указатель
    //  CHILD pbuffer;  // контексты рендеринга сцены
    SCENE();
    virtual ~SCENE();
    virtual bool update();
    virtual void event();
    virtual void step(unbase::TIME&);
    virtual void draw(unsigned int mode=RENDERMODE::geom|RENDERMODE::matl);
    operator string();
    //tolua_end
    void drawshadow(const LIGHT&);
  };//tolua_export
  
  class SCNGROUP{//tolua_export
  public:
    typedef map<string,SCENE*>::iterator ITER;
  protected:
    typedef map<string,SCENE*> POOL;
    POOL pool;
  public:
    ITER begin();
    ITER end();
    //tolua_begin
    SCNGROUP();
    virtual ~SCNGROUP();
    void operator()(string&/** k="" asnil**/,SCENE*&);
    /**tolua_getindex {**/
    SCENE* get(string);
    /**}**/
    /**tolua_setindex {**/
    void set(string,SCENE*);
    /**}**/
    operator string();
    //tolua_end
  };//tolua_export
}//tolua_export
