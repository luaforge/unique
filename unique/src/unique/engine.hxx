#pragma once
#include "unoal.hxx"
#include "unogl.hxx"
#include "unobj.hxx"

namespace unique{//tolua_export
  class ENGINE{//tolua_export
  public:
    //tolua_begin
    unbase::CONTEXTS render; // Rendering contexts
    unobj::SCNGROUP  scene;  // Scenes
    unbase::CONTEXT* eventer;// 
    unbase::TIME     time;   // Main time
    unbase::TIME     steptime; // Simulation time
    unbase::TIME     drawtime; // Rendering time
    bool     run;    // Looping
    double   fps;// Frame per second
    
    ENGINE();
    ~ENGINE();
    void loop();
    void draw();
    void step();
    void event();
    operator string();
    //tolua_end
  };//tolua_export

  extern ENGINE engine;//tolua_export
}//tolua_export
