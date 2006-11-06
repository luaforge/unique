#pragma once
#include"unbase.hxx"
#include"oglext.hxx"
#include"keybd.hxx"

namespace unogl{//tolua_export
  class KEYS{//tolua_export
  public:
    static const KEY defkey;
    typedef deque<KEY> CONT;
    typedef deque<KEY>::iterator ITER;
    CONT array;
    //tolua_begin
    KEYS();
    ~KEYS();
    void operator()(int&num/**=-1 asnil**/,KEY*&key/**=NULL asnil**/); //iterator
    const KEY* operator[](int); // get
    operator string();
  };
  //tolua_end
  
  class PIXELMODE{//tolua_export
  public:
    //tolua_begin
    int red; // 8
    int green; // 8
    int blue; // 8
    int alpha; // 8
    int depth; // 24
    int stencil; // 8
    PIXELMODE();
  };
  //tolua_end
  
  class GRAPHCONTEXT: public unbase::CONTEXT{//tolua_export
  protected:
    vec2 osize,opointer;
  public:
    //tolua_begin
    // VidSize constants
    static tolua_readonly unmath::vec2 _320x240;
    static tolua_readonly unmath::vec2 _640x480;
    static tolua_readonly unmath::vec2 _800x600;
    static tolua_readonly unmath::vec2 _1024x768;
    // Properties
    unmath::vec2 size,pointer,pointervel;
    unogl::KEYS key;
    int buffering; // 1 - single buffering, 2 - double buffering (default 1)
    int sampling;  // 1 - without multisample, 2 - 2x multisample,
    // 4 - 4x multisample (default 1)
    PIXELMODE pixel;
    // Constructor / destructor
    GRAPHCONTEXT();
    virtual ~GRAPHCONTEXT();
    // Opening & closing context
    //virtual bool open();
    //virtual void close();
    virtual void RendererInfo();
    virtual void InitExtensions();
    // Binding context
    virtual void bind();  // Binding context (similar make current)
    virtual void ubind(); // Unbinding context (similar swap buffer or flush buffer)
    virtual void clear(); // Clearing context
  }; 
}
//tolua_end
