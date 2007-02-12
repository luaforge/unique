#pragma once
#include"unbase.hxx"
#include"unmath.hxx"

#if _WIN32
#  include<windows.h>
#endif
#if _LINUX
#  include<glx.h>
#endif

#undef GL_GLEXT_PROTOTYPES

#include<gl.h>
#include<glu.h>
#include<glext.h>

namespace unogl{
  
#ifdef OGL_DEBUG_MODE
#  define OGL_CHECKERROR() unogl::glCheckError(__FILE__,__LINE__);
#else
#  define OGL_CHECKERROR()
#endif
#define OGL_DEBUG() OGL_CHECKERROR()
  
  extern vec3& gl_CameraPosition();
  extern quat& gl_CameraRotation();
  extern mat4& gl_RotateProjectionMatrix();
  extern mat4& gl_RotateProjectionMatrixInv();
  extern mat4& gl_TranslateProjectionMatrix();
  extern mat4& gl_TranslateProjectionMatrixInv();
  extern int&  gl_Lights();
  
#include"oglext.decl.hxx"
  
#define GLEXT_FUNC(name,type,real) extern PFN##type##PROC name;
#include"oglext.func.hxx"
#undef GLEXT_FUNC
  
  extern void glInitNamesArray();
  extern void glGenNames(GLsizei n,GLuint* names);
  extern void glDeleteNames(GLsizei n,const GLuint* names);
  typedef void (*glExtFuncPtr)(void);
  extern glExtFuncPtr glGetProcAddress(const char* name);
  extern void glInitExtensions();
  extern bool glCheckError(const char* srcfile, const int srcline);
  
  /*
    PLANE - 
  */
  /*
    class PLANE{
    protected:
    vec4 _coord;
    bool _enable;
    public:
    // Methods
    PLANE(){ Enable(true); }
    PLANE(scalar a, scalar b, scalar c, scalar d): _coord(a, b, c, d){ Enable(true); }
    PLANE(vec4 p): _coord(p){ Enable(true); }
    ~PLANE(){}
    // Properties
    vec4& Coord() const{ return (vec4&)_coord; }
    void  Coord(vec4 p){ _coord=p; }
    bool  Enable() const{ return _enable; }
    void  Enable(bool s){ _enable=s; }
    };
  */
  /*
    CLIP
  */
  /*
    class CLIP{
    protected:
    PLANE _plane[6];
    public:
    // Methods
    CLIP(){ for(GLuint i=0; i<6; i++)_plane[i].Enable(false); }
    CLIP(PLANE p){ for(GLuint i=0; i<6; i++)_plane[i].Enable(false); Plane0(p); }
    CLIP(PLANE p0, PLANE p1){ for(GLuint i=0; i<6; i++)_plane[i].Enable(false);
    Plane0(p0); Plane1(p1); }
    CLIP(PLANE p0, PLANE p1, PLANE p2){
    for(GLuint i=0; i<6; i++)_plane[i].Enable(false);
    Plane0(p0); Plane1(p1); Plane2(p2); }
    CLIP(PLANE p0, PLANE p1, PLANE p2, PLANE p3){
    for(GLuint i=0; i<6; i++)_plane[i].Enable(false);
    Plane0(p0); Plane1(p1); Plane2(p2); Plane3(p3); }
    CLIP(PLANE p0, PLANE p1, PLANE p2, PLANE p3, PLANE p4){
    for(GLuint i=0; i<6; i++)_plane[i].Enable(false);
    Plane0(p0); Plane1(p1); Plane2(p2); Plane3(p3); Plane4(p4); }
    CLIP(PLANE p0, PLANE p1, PLANE p2, PLANE p3, PLANE p4, PLANE p5){
    for(GLuint i=0; i<6; i++)_plane[i].Enable(false);
    Plane0(p0); Plane1(p1); Plane2(p2); Plane3(p3); Plane4(p4); Plane4(p5); }
    ~CLIP(){}
    
    void Bind(){
    for(GLuint i=0; i<6; i++) if(_plane[i].Enable()){
    scalar* p=_plane[i].Coord();
    GLdouble cp[4]={p[0], p[1], p[2], p[3]};
    glClipPlane(GL_CLIP_PLANE0+i, cp);
    glEnable(GL_CLIP_PLANE0+i);
    }else{
    glDisable(GL_CLIP_PLANE0+i);
    }
    }
    void uBind(){
    for(GLuint i=0; i<6; i++){
    glDisable(GL_CLIP_PLANE0+i);
    }
    }
    // Properties
    PLANE& Plane0() const{ return (PLANE&)_plane[0]; }
    void Plane0(PLANE p){ _plane[0]=p; }
    PLANE& Plane1() const{ return (PLANE&)_plane[1]; }
    void Plane1(PLANE p){ _plane[1]=p; }
    PLANE& Plane2() const{ return (PLANE&)_plane[2]; }
    void Plane2(PLANE p){ _plane[2]=p; }
    PLANE& Plane3() const{ return (PLANE&)_plane[3]; }
    void Plane3(PLANE p){ _plane[3]=p; }
    PLANE& Plane4() const{ return (PLANE&)_plane[4]; }
    void Plane4(PLANE p){ _plane[4]=p; }
    PLANE& Plane5() const{ return (PLANE&)_plane[5]; }
    void Plane5(PLANE p){ _plane[5]=p; }
    };
  */
}
