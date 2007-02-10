#pragma once
#include"unbase.hxx"

#include<map>

namespace unbase{//tolua_export
  // Interface context class
  class CONTEXT{//tolua_export
  protected:
    virtual void RendererInfo();
  public:
    //tolua_begin
    STATE state;
    CONTEXT();
    virtual ~CONTEXT();
    // Renderer info
    /**const**/ string vendor;
    /**const**/ string renderer;
    /**const**/ string version;
    /**const**/ string extensions;
    // Opening & closing context
    virtual bool open();
    virtual void close();
    // Binding / Unbinding
    virtual void bind();
    virtual void ubind();
    virtual void clear();
    // Cast
    virtual operator string();
  };
  //tolua_end
  
  class CTXGROUP{//tolua_export
  protected:
    typedef map<string,CONTEXT*> POOL;
    POOL pool;
  public:
    typedef map<string,CONTEXT*>::iterator ITER;
    ITER begin();
    ITER end();
    //tolua_begin
    CTXGROUP();
    ~CTXGROUP();
    void operator()(string&/**n="" asnil**/,CONTEXT*&/**c=NULL**/);
    //CONTEXT *& operator[](string);
    /**tolua_getindex {**/
    CONTEXT* get(string);
    /**}**/
    /**tolua_setindex {**/
    void set(string,CONTEXT*);
    /**}**/
    operator string();
  };
  //tolua_end
}//tolua_export
