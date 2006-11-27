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

#include<map>

namespace unobj{//tolua_export
  struct RENDERMODE{//tolua_export
    //tolua_begin
    enum {
      geom = 0x1, // рендерить геометрию (без материалов)
      matl = 0x2, // рендерить с материалами (полный рендеринг)
      name = 0x4, // генерировать имена (генерация имен для выбора объекта)
      axis = 0x8, // рисовать оси (рисовать оси объекта, пересекающиеся в его центре)
      imad = 0x10,// рисовать схематично мнимые объекты (лампы, камеры, системы частиц) для калибровки
      hier = 0x20,// рисовать связи иерархии группы и проч.
      quer = 0x40,// подсчет отрендеренных фрагментов
      shad = 0x80,// рендеринг тени от геометрии объекта
    };
    //tolua_end
  };//tolua_export

  struct RENDERTYPE{//tolua_export
    enum {
      normal,
      blend,
    };
  };//tolua_export

  class GROUP;
  class SCENE;
  class OBJECT{//tolua_export
  protected:
    unmath::vec3 opos,ovel;
    unmath::quat orot,oang;
    unmath::mat4 omtx;
    bool oshadow;
  public:
    //tolua_begin
    unsigned int rtype; // object render type
    unsigned int rmode; // object render mode
    bool visible; // object visibility
    string name;  // object name
    bool shadow;  // caste shadow
    /* Hierarhy */
    OBJECT* target;// object target
    OBJECT* locate;// locate object
    GROUP* parent; // object parent
    SCENE* scene;  // object scene
    /* Object Geometry */
    unmath::vec3 boundbox;
    unmath::scalar boundsphere;
    /* Axis */
    bool showaxis;
    unmath::vec3 axlen;  // Axis length
    unmath::vec2 axend;  // Axis End Point size
    /* Object propertyes */
    unmath::vec3 pos; // Position
    unmath::vec3 vel; // Linear velocity
    unmath::quat rot; // Orientation
    unmath::quat ang; // Angular velocity
    unmath::mat4 mtx; // Matrix
    //  MATERIAL *mat; // Material
    unvis::MATGROUP mat;
    //BODY     *body;  // Phy Body
    /* Selection Query */
    unsigned int id;  // OpenGL имя объекта
    bool   sel, act;  // выборка и активность
    /* Occlusion Query */
    unsigned int qid;      // Идентификатор для Occlusion Query
    unsigned int num_frag; // Число отрендереных фрагментов
    unsigned int num_tri;  // Число отправленных на конвейер треугольников
    
    unbase::STATE state;
    /* Constructor - Destructor */
    OBJECT();
    virtual ~OBJECT();
    /* Selection query          */
    //tolua_end
    virtual void BindName(unsigned int mode);
    virtual void uBindName(unsigned int mode);
    /* Selecting                */
    virtual void select(unsigned int);
    /* Occlusion query          */
    virtual void BindQuery(unsigned int mode);
    virtual void uBindQuery(unsigned int mode);
    virtual GLuint QueryFrag() const; // Rendered fragments
    /* Object Matrix            */
    virtual void BindLoc();// Установка OpenGL модельной матрицы в локальную координатную систему объекта
    virtual void uBindLoc();
    virtual const mat4 matrix()const;
    virtual const mat4 locatematrix()const;
    /* Object Material          */
    virtual void BindMat(unsigned int mode); // Материал
    virtual void BindMat(unsigned int mode,string name); // Материал
    virtual void uBindMat(unsigned int mode);
    virtual void uBindMat(unsigned int mode,string name);
    //tolua_begin
    /* Object Draw              */
    virtual void drawaxis(unsigned int mode=RENDERMODE::axis);  // Draw object axis (in local coords)
    virtual void drawmodel(unsigned int mode=RENDERMODE::imad); // Draw object scheme
    virtual void draw(unsigned int mode=RENDERMODE::geom|RENDERMODE::matl);// Draw object
    virtual void casteshadow(const vec3&);// построение теневого объема объекта
    /* Simulation - Action      */
    virtual void step(unbase::TIME&);
    /* Handlers */
    virtual void event(unogl::GRAPHCONTEXT&);
    //tolua_end
    virtual void stepHandler(unbase::TIME&event);
    virtual void drawHandler(unsigned int event);
    virtual void eventHandler(unogl::GRAPHCONTEXT& event);
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
    bool autoload;
  public:
    ITER begin();
    ITER end();
    string fullhiername(string n="");
    GROUP(bool autoload);
    //tolua_begin
    void operator()(string&/** k="" asnil**/,OBJECT*&);
    /**tolua_getindex {**/
    OBJECT* get(string);
    /**}**/
    /**tolua_setindex {**/
    void set(string,OBJECT*);
    /**}**/
    GROUP();
    virtual ~GROUP();
    virtual void draw(unsigned int mode=RENDERMODE::geom);
    virtual void step(unbase::TIME&);
    virtual operator string();
    //virtual string __info();
    //tolua_end
    virtual void select(unsigned int);
    virtual void event(unogl::GRAPHCONTEXT&);
    virtual void casteshadow(const unmath::vec3&);
  };//tolua_export
}//tolua_export
