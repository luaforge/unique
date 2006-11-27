#include"pixelbuffer.linux.hxx"

namespace unfbo{
  using namespace unogl;

  PIXELBUFFER::PIXELBUFFER():GRAPHCONTEXT(),xdisplay(NULL),xpbuffer(0),xscreen(0),texture(false){}
  PIXELBUFFER::~PIXELBUFFER(){close();}
  bool PIXELBUFFER::open(){
    if(xdisplay)return false;
    xdisplay=glXGetCurrentDisplay();
    xscreen=DefaultScreen(xdisplay);

    vector<int> va;
    va.push_back(GLX_RENDER_TYPE);
    va.push_back(GLX_RGBA_BIT);
    va.push_back(GLX_DRAWABLE_TYPE);
    va.push_back(GLX_PBUFFER_BIT);
    //if(buffering==2)
    va.push_back(GLX_DOUBLEBUFFER);
    va.push_back(false);
    if(pixel.red>0){
      va.push_back(GLX_RED_SIZE);
      va.push_back(pixel.red);
    }
    if(pixel.green>0){
      va.push_back(GLX_GREEN_SIZE);
      va.push_back(pixel.green);
    }
    if(pixel.blue>0){
      va.push_back(GLX_BLUE_SIZE);
      va.push_back(pixel.blue);
    }
    if(pixel.alpha>0){
      va.push_back(GLX_ALPHA_SIZE);
      va.push_back(pixel.alpha);
    }
    if(pixel.depth){
      va.push_back(GLX_DEPTH_SIZE);
      va.push_back(pixel.depth);
    }
    if(pixel.stencil) {
      va.push_back(GLX_STENCIL_SIZE);
      va.push_back(pixel.stencil);
    }
    va.push_back(GLX_FLOAT_COMPONENTS_NV);
    va.push_back(true);
    if(sampling>1){
      va.push_back(GLX_SAMPLE_BUFFERS_ARB);
      va.push_back(true);
      va.push_back(GLX_SAMPLES_ARB);
      va.push_back(sampling);
    }
    va.push_back(0);

    int cnt;

    vector<int> pa;
    pa.push_back(GLX_LARGEST_PBUFFER);
    pa.push_back(false);
    pa.push_back(0);
    
    const char*extensions=glXQueryExtensionsString(xdisplay,xscreen);
    if(strstr(extensions,"GLX_SGIX_pbuffer")&&strstr(extensions,"GLX_SGIX_fbconfig")){
      pa.push_back(0);
      fbconfig=glXChooseFBConfig(xdisplay,xscreen,&va[0],&cnt);
      if(!fbconfig){
	state=unbase::STATE(false,"glXChooseFBConfig failed");
	return false;
      }
      xpbuffer=glXCreatePbuffer(xdisplay,fbconfig[0],/*(int)size.width,(int)size.height,*/&pa[0]);
      if(!xpbuffer){
	state=unbase::STATE(false,"glXCreateGLXPbuffer failed");
	return false;
      }
      //xcontext=glXCreateContextWithConfig(xdisplay,fbconfig[0],GLX_RGBA_TYPE,glXGetCurrentContext(),true);
      if(!xcontext){
	state=unbase::STATE(false,"glXCreateContextWithConfig failed");
	return false;
      }
    }else{
      pa.push_back(GLX_PBUFFER_WIDTH);
      pa.push_back((int)size.width);
      pa.push_back(GLX_PBUFFER_HEIGHT);
      pa.push_back((int)size.height);
      pa.push_back(0);

      fbconfig=glXChooseFBConfig(xdisplay,xscreen,&va[0],&cnt);
      if(!fbconfig){
	state=unbase::STATE(false,"glXChooseFBConfig failed");
	xpbuffer=glXCreatePbuffer(xdisplay,fbconfig[0],&pa[0]);
	if(!xpbuffer){
	  state=unbase::STATE(false,"glXCreatePbuffer failed");
	  return false;
	}
	xvisual=glXGetVisualFromFBConfig(xdisplay,fbconfig[0]);
	if(!xvisual){
	  state=unbase::STATE(false,"glXGetVisualFromFBConfig failed");
	  return false;
	}
	xcontext=glXCreateContext(xdisplay,xvisual,glXGetCurrentContext(),true);
	if(!xcontext){
	  state=unbase::STATE(false,"glXCreateContext failed");
	  return false;
	}
      }
      // in error case
      //xpbuffer=glXGetCurrentDrawable();
      //xcontext=glXGetCurrentContext();
    }
    state=unbase::STATE(true,"PIXELBUFFER Inited normally");
    return true;
  }
  void PIXELBUFFER::close(){
    if(!xdisplay)return;
    if(xcontext)glXDestroyContext(xdisplay,xcontext);
    if(xpbuffer)glXDestroyPbuffer(xdisplay,xpbuffer);
  }
  void PIXELBUFFER::bind(){
    if(xdisplay && xpbuffer){
      if(!glXMakeCurrent(xdisplay,xpbuffer,xcontext))state=unbase::STATE(false,"glXMakeCurrent filed!");
    }
  }
  void PIXELBUFFER::ubind(){
    for(unvis::TEXGROUP::ITER i=texture.begin();i!=texture.end();i++){
      i->second->copy();
    }
  }
}
