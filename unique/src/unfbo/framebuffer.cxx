#include "framebuffer.hxx"

namespace unfbo{
  using namespace unogl;

  FRAMEBUFFER::FRAMEBUFFER():GRAPHCONTEXT(),depth(NULL),stencil(NULL),
			     odepth(NULL),ostencil(NULL){
    glGenFramebuffers(1,&glid);
    OGL_DEBUG();
  }
  FRAMEBUFFER::~FRAMEBUFFER(){
    glDeleteFramebuffers(1,&glid);
    OGL_DEBUG();
  }
  void FRAMEBUFFER::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER,glid);
    OGL_DEBUG();
    update();
  }
  void FRAMEBUFFER::check(){
    GLenum status=glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(status){
    case GL_FRAMEBUFFER_COMPLETE:
      state=unbase::STATE(true,"FrameBuffer complete");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      state=unbase::STATE(false,"FrameBuffer incomplete attachment");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      state=unbase::STATE(false,"FrameBuffer incomplete missing attachment");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT:
      state=unbase::STATE(false,"FrameBuffer incomplete duplicate attachment");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
      state=unbase::STATE(false,"FrameBuffer incomplete dimensions");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
      state=unbase::STATE(false,"FrameBuffer draw buffer");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
      state=unbase::STATE(false,"FrameBuffer read buffer");
      break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
      state=unbase::STATE(false,"FrameBuffer unsupported");
      /* choose different formats */
      break;
    default:
      state=unbase::STATE(false,"FrameBuffer programming error");
      /* programming error; will fail on all hardware */
    }
  }
  void FRAMEBUFFER::ubind(){
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    OGL_DEBUG();
  }

  bool FRAMEBUFFER::update(){
    // Update
    if(stencil)stencil->update();
    if(depth)    depth->update();
    for(RBGROUP::ITER i=color.begin();
	i!=color.end();i++,i->second->update());
    // Attach
    if(ostencil!=stencil){
      ostencil=stencil;
      stencil->attach(GL_STENCIL_ATTACHMENT);
    }
    if(odepth!=depth){
      odepth=depth;
      depth->attach(GL_DEPTH_ATTACHMENT);
    }
    unsigned int j=0;
    if(color.update())
      for(RBGROUP::ITER i=color.begin();
	  i!=color.end();i++,i->second->attach(GL_COLOR_ATTACHMENT0+j),j++);
    check();
  }
}
