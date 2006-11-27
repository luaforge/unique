#pragma once
#include"unogl.hxx"
#include"unvis.hxx"
#include"renderbuffer.hxx"

namespace unfbo{//tolua_export
  class FRAMEBUFFER: public unogl::GRAPHCONTEXT{//tolua_export
  protected:
    GLuint glid;
    RENDERBUFFER* odepth;
    RENDERBUFFER* ostencil;
  public:
    //tolua_begin
    RBGROUP color;
    RENDERBUFFER* depth;
    RENDERBUFFER* stencil;

    FRAMEBUFFER();
    virtual ~FRAMEBUFFER();

    void bind();
    void ubind();
    void check();
    bool update();
    //tolua_end
  };//tolua_export
}//tolua_export
