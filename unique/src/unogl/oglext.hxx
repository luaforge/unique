#pragma once
#include"unbase.hxx"
#include"unmath.hxx"

#define GL_GLEXT_PROTOTYPES

#ifdef _WIN32
#  include<windows.h>
#else
#  define GLX_GLXEXT_PROTOTYPES
#  include<glx.h>
#endif

#include<gl.h>
#include<glu.h>
#define GL_GLEXT_PROTOTYPES
#include<glext.h>

#ifdef OGL_DEBUG_MODE
#  define OGL_CHECKERROR() OGLEXT::CheckGLError(__FILE__,__LINE__,"");
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
extern GLint& gl_Lights();

// Common extensions synonyms
// Renderbuffer
# define GL_RENDERBUFFER          GL_RENDERBUFFER_EXT
# define GL_STENCIL_INDEX1        GL_STENCIL_INDEX1_EXT
# define GL_STENCIL_INDEX4        GL_STENCIL_INDEX4_EXT
# define GL_STENCIL_INDEX8        GL_STENCIL_INDEX8_EXT
# define GL_STENCIL_INDEX16       GL_STENCIL_INDEX16_EXT
//# define GL_DEPTH_COMPONENT24     GL_DEPTH_COMPONENT24_EXT
// Framebuffer
# define GL_FRAMEBUFFER           GL_FRAMEBUFFER_EXT
# define GL_COLOR_ATTACHMENT0     GL_COLOR_ATTACHMENT0_EXT
# define GL_DEPTH_ATTACHMENT      GL_DEPTH_ATTACHMENT_EXT
# define GL_STENCIL_ATTACHMENT    GL_STENCIL_ATTACHMENT_EXT
# define GL_FRAMEBUFFER_COMPLETE  GL_FRAMEBUFFER_COMPLETE_EXT
# define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT           GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT
# define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT   GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT
# define GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT
# define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS  GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT
# define GL_FRAMEBUFFER_INCOMPLETE_FORMATS     GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT
# define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT
# define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT
# define GL_FRAMEBUFFER_UNSUPPORTED  GL_FRAMEBUFFER_UNSUPPORTED_EXT
# define GL_FRAMEBUFFER_STATUS_ERROR GL_FRAMEBUFFER_STATUS_ERROR_EXT
// Limits
# define GL_MAX_COLOR_ATTACHMENTS GL_MAX_COLOR_ATTACHMENTS_EXT
# define GL_MAX_RENDERBUFFER_SIZE GL_MAX_RENDERBUFFER_SIZE_EXT
// MipMap
extern PFNGLGENERATEMIPMAPEXTPROC          glGenerateMipmap;
// Renderbuffer
extern PFNGLGENRENDERBUFFERSEXTPROC        glGenRenderbuffers;
extern PFNGLDELETERENDERBUFFERSEXTPROC     glDeleteRenderbuffers;
extern PFNGLRENDERBUFFERSTORAGEEXTPROC     glRenderbufferStorage;
extern PFNGLBINDRENDERBUFFEREXTPROC        glBindRenderbuffer;
// Framebuffer
extern PFNGLGENFRAMEBUFFERSEXTPROC         glGenFramebuffers;
extern PFNGLDELETEFRAMEBUFFERSEXTPROC      glDeleteFramebuffers;
extern PFNGLBINDFRAMEBUFFEREXTPROC         glBindFramebuffer;
extern PFNGLFRAMEBUFFERTEXTURE1DEXTPROC    glFramebufferTexture1D;
extern PFNGLFRAMEBUFFERTEXTURE2DEXTPROC    glFramebufferTexture2D;
extern PFNGLFRAMEBUFFERTEXTURE3DEXTPROC    glFramebufferTexture3D;
extern PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbuffer;
extern PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC  glCheckFramebufferStatus;

# ifdef _WIN32
#  define REG_GLEXT_FUNC(type,name) name=(type)wglGetProcAddress(#name)
# else
//extern __GLXextFuncPtr glXGetProcAddressARB (const GLubyte *);
#  define REG_GLEXT_FUNC(type,name) name=(type)glXGetProcAddressARB((GLubyte*)#name)
# endif

void glInitNamesArray();
void glGenNames(GLsizei n,GLuint* names);
void glDeleteNames(GLsizei n,const GLuint* names);

class OGLEXT{
 public:
  const char* vendor;
  const char* renderer;
  const char* version;
  const char* extensions;

  OGLEXT();
  virtual ~OGLEXT();
  
  void Init();
  void* GetProcAddress(const char* extname);
  static bool CheckGLError(const char* srcfile,const int srcline,const char* funcname);
  void gl_error(int& errcode,string& errname);
 public:
};

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
