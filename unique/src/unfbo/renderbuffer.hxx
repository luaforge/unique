#pragma once
#include"unogl.hxx"
#include"unvis.hxx"

namespace unfbo{//tolua_export
  class RENDERBUFFER{//tolua_export
  public:
    //tolua_begin
    enum FORMAT{
      rgb      =GL_RGB,
      rgb8     =GL_RGB8,
      rgb16    =GL_RGB16,
      rgba     =GL_RGBA,
      rgba8    =GL_RGBA8,
      rgba16   =GL_RGBA16,
      depth    =GL_DEPTH_COMPONENT,
      depth24  =GL_DEPTH_COMPONENT24,
      stencil  =GL_STENCIL_INDEX,
      stencil1 =GL_STENCIL_INDEX1,
      stencil4 =GL_STENCIL_INDEX4,
      stencil8 =GL_STENCIL_INDEX8,
      stencil16=GL_STENCIL_INDEX16
    };
    //tolua_end
  protected:
    unsigned int glid;
    unsigned int oformat;
    unmath::vec2 osize;
  public:
    //tolua_begin
    unsigned int format;
    unmath::vec2 size;

    RENDERBUFFER();
    virtual ~RENDERBUFFER();

    virtual void bind();
    virtual void ubind();
    virtual void attach(unsigned int at);
    virtual void update();
    //tolua_end
  };//tolua_export

  class RENDERTEXTURE: public RENDERBUFFER{//tolua_export
  protected:
  public:
    //tolua_begin
    unvis::TEXTURE* texture;
    unsigned int level;
    unsigned int cubeside;
    unsigned int zoffset;

    RENDERTEXTURE();
    virtual ~RENDERTEXTURE();

    virtual void bind();
    virtual void ubind();
    virtual void attach(unsigned int at);
    virtual void update();
    //tolua_end
  };//tolua_export

  class RBGROUP{//tolua_export
  protected:
    bool updated;
    
    typedef map<string,RENDERBUFFER*> POOL;
    POOL pool;
  public:
    typedef map<string,RENDERBUFFER*>::iterator ITER;
    ITER begin();
    ITER end();
    //tolua_begin
    RBGROUP();
    ~RBGROUP();
    
    void operator()(string&/**n="" asnil**/,RENDERBUFFER*&/**c=NULL**/);
    //CONTEXT *& operator[](string);
    /**tolua_getindex {**/
    RENDERBUFFER* get(string);
    /**}**/
    /**tolua_setindex {**/
    void set(string, RENDERBUFFER*);
    /**}**/
    operator string();
    bool update();
    //tolua_end
  };//tolua_export
}//tolua_export
