/************************************************Fenix***

Header file: 

Copyleft (C) 2005 RareSky Zone

Comments:
    It is module for SolvEngine.

Bug report to:
    tonder@trktvs.ru

Author:
    Fenix R.S.

**********************************************************/

#pragma once
#include"mesh.hxx"

namespace ungeom{//tolua_export
  class HMAP: public MESH{//tolua_export
  protected:
    vec2 otexcrd;
    vec3 odensity;
  public:
    //tolua_begin
    vec2 texcrd;  // Step texture coords
    vec3 density; // Step size per height width depth
    HMAP();
    virtual ~HMAP();
    
    bool update();
    operator string();
    //tolua_end
  };//tolua_export
}//tolua_export
