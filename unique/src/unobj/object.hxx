/***************************************************************************
 *            object.hpp
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
#include"unbase.hxx"
#include"unogl.hxx"
//#include"unphy.hxx"
#include"unvis.hxx"
#include"mode.hxx"

#include<map>

namespace unobj{//tolua_export
  class GROUP;
  class SCENE;
  class OBJECT{//tolua_export
  protected:
    unmath::vec3 opos,ovel;
    unmath::quat orot,oang;
    unmath::mat4 omtx;
  public:
    //tolua_begin
    unobj::MODE mode; // object render mode
    string name;      // object name
    /* Hierarhy */
    unobj::OBJECT* target;// object target
    unobj::OBJECT* locate;// locate object
    unobj::GROUP*  parent;// object parent
    unobj::SCENE*  scene; // object scene
    /* Object Geometry */
    unmath::vec3 boundbox;
    unmath::scalar boundsphere;
    /* Axis */
    unmath::vec3 axlen; // axis length
    unmath::vec2 axend; // axis End Point size
    /* Object propertyes */
    unmath::vec3 pos; // position
    unmath::vec3 vel; // linear velocity
    unmath::quat rot; // orientation
    unmath::quat ang; // angular velocity
    unmath::mat4 mtx; // matrix
    unvis::MATERIAL* mat; // material
    unbase::TIME time; // last step time
    unobj::RENDER* render; // render
    //BODY     *body;  // Phy Body
    /* Selection Query */
    unsigned int id;  // OpenGL object name id
    bool select; // Selected
    bool active; // Activity
    /* Occlusion Query */
    unsigned int qid;      // Occlusion Query OpenGL id
    unsigned int fragments; // Num of rendered fragments
    unsigned int triangles; // Num of rendered triangles
    
    unbase::STATE state;   // Object state
    /* Constructor - Destructor */
    OBJECT();
    virtual ~OBJECT();
    /* Selection query          */
    //tolua_end
    virtual void bind_name();
    virtual void ubind_name();
    /* Occlusion query          */
    virtual void bind_query();
    virtual void ubind_query();
    /* Object Matrix            */
    virtual void bind_loc();
    virtual void ubind_loc();
    virtual const mat4 matrix()const;
    virtual const mat4 locatematrix()const;
    /* Object Material          */
    virtual void bind_mat();
    virtual void ubind_mat();
    //tolua_begin
    /* Object Draw              */
    virtual void draw_axis();  // Draw object axis (in local coords)
    virtual void draw_model(); // Draw object scheme
    virtual void draw_geom(const unobj::MODE&);// Draw object real geometry
    virtual void draw(const unobj::MODE&);// Draw object
    /* Simulation - Action      */
    virtual void step(const unbase::TIME&);
    /* Handlers */
    virtual void event(unogl::GRAPHCONTEXT&);
    //tolua_end
    virtual void step_handler(const unbase::TIME&);
    virtual void draw_handler(const unobj::MODE&);
    virtual void event_handler(unogl::GRAPHCONTEXT&);
    //tolua_begin
    virtual bool update();
    virtual operator string();
    //virtual string __info();
    //tolua_end
  };//tolua_export
  
  class GROUP: public OBJECT{//tolua_export
  public:
    typedef map<string,OBJECT*> POOL;
    typedef map<string,OBJECT*>::iterator ITER;
    POOL pool;
  public:
    ITER begin();
    ITER end();
    //string fullhiername(string n="");
    //tolua_begin
    void operator()(string&/** k="" asnil**/,OBJECT*&); // iterator
    int operator~(); // num of childs
    /**tolua_getindex {**/
    OBJECT* get(string); // get child
    /**}**/
    /**tolua_setindex {**/
    void set(string,OBJECT*); // set child
    /**}**/
    
    GROUP();
    virtual ~GROUP();
    
    virtual void step(const unbase::TIME&);
    virtual operator string();
    //tolua_end
    virtual void event(unogl::GRAPHCONTEXT&);
  };//tolua_export
}//tolua_export
