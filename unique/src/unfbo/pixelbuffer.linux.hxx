#if _LINUX && !_MINGW
#pragma once
#include"unogl.hxx"
#include"unvis.hxx"

namespace unfbo{
  class PIXELBUFFER: public unogl::GRAPHCONTEXT{
  protected:
    Display*     xdisplay;
    GLXPbuffer   xpbuffer;
    GLXContext   xcontext;
    XVisualInfo* xvisual;
    GLXFBConfig* fbconfig;
    int          xscreen;
  public:
    unvis::TEXGROUP texture;
    PIXELBUFFER();
    virtual ~PIXELBUFFER();
    virtual bool open();
    virtual void close();
    virtual void bind();
    virtual void ubind();
  };
}

#endif
