#pragma once
#include"unobj.hxx"
#include"unoal.hxx"

namespace unsnd{//tolua_export
  class LISTEN: public unobj::OBJECT{//tolua_export
  protected:
    vec3 _vel;
    scalar ogain;
  public:
    //tolua_begin
    scalar gain;
    
    LISTEN();
    virtual ~LISTEN();
    //tolua_end
    virtual void bind();
    virtual void ubind();
    virtual bool update();
  };//tolua_export
}//tolua_export
