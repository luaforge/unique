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
  
  class CONTEXTS{//tolua_export
  public:
    typedef map<string,CONTEXT*> CONT;
    typedef map<string,CONTEXT*>::iterator ITER;
    CONT array;
    //tolua_begin
    CONTEXTS();
    ~CONTEXTS();
    void operator()(string&/**n="" asnil**/,CONTEXT*&/**c=NULL**/);
    //tolua_end
    //CONTEXT *& operator[](string);
    CONTEXT* get(string);
    void set(string, CONTEXT*);
    //tolua_begin
    /**CONTEXT* tolua_index(string,get,set);**/
    operator string();
  };
  //tolua_end
}//tolua_export
