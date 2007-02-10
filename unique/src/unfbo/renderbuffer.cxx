#include"renderbuffer.hxx"

namespace unfbo{
  using namespace unogl;
  
  RENDERBUFFER::RENDERBUFFER():size(1024,768){
    glGenRenderbuffers(1,&glid);
    OGL_DEBUG();
  }
  RENDERBUFFER::~RENDERBUFFER(){
    glDeleteRenderbuffers(1,&glid);
    OGL_DEBUG();
  }
  void RENDERBUFFER::bind(){
    glBindRenderbuffer(GL_RENDERBUFFER,glid);
    OGL_DEBUG();
  }
  void RENDERBUFFER::ubind(){
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    OGL_DEBUG();
  }
  void RENDERBUFFER::update(){
    if(format!=oformat||size!=osize){
      oformat=format;
      osize=size;
      bind();
      glRenderbufferStorage(GL_RENDERBUFFER,format,(GLsizei)size.x,(GLsizei)size.y);
      //glRenderbufferStorage(GL_RENDERBUFFER,GL_STENCIL_INDEX,512,512);
      cout<<"update rb: "<<glid<<" size:"<<string(size)<<" format:"<<format<<endl;
      OGL_DEBUG();
      ubind();
    }
  }
  void RENDERBUFFER::attach(unsigned int at){
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,at,GL_RENDERBUFFER,glid);
    cout<<"attach rb: "<<typeid(this).name()<<" rb_glid: "<<glid<<endl;
    OGL_DEBUG();
  }

  RENDERTEXTURE::RENDERTEXTURE():texture(NULL),level(0),cubeside(0),zoffset(0){}
  RENDERTEXTURE::~RENDERTEXTURE(){}
  void RENDERTEXTURE::bind(){}
  void RENDERTEXTURE::ubind(){}
  void RENDERTEXTURE::attach(unsigned int at){
    if(texture){
      switch(texture->typetarget){
      case GL_TEXTURE_1D: glFramebufferTexture1D(GL_FRAMEBUFFER,at,GL_TEXTURE_1D,
						 texture->glid,level);
	OGL_DEBUG(); break;
      case GL_TEXTURE_2D: glFramebufferTexture2D(GL_FRAMEBUFFER,at,GL_TEXTURE_2D,
						 texture->glid,level);
	OGL_DEBUG(); break;
      case GL_TEXTURE_3D: glFramebufferTexture3D(GL_FRAMEBUFFER,at,GL_TEXTURE_3D,
						 texture->glid,level,zoffset);
	OGL_DEBUG(); break;
      case GL_TEXTURE_CUBE_MAP: glFramebufferTexture2D(GL_FRAMEBUFFER,at,
						       GL_TEXTURE_CUBE_MAP_POSITIVE_X+cubeside,texture->glid,level);
	OGL_DEBUG(); break;
      }
    }
  }
  void RENDERTEXTURE::update(){
    if(format!=oformat||size!=osize){
      oformat=format;
      osize=size;
      if(texture){
	texture->format=format;
	texture->chan=format;
	texture->bind();
	switch(texture->typetarget){
	case GL_TEXTURE_1D: glTexImage1D(texture->typetarget,0,texture->chan,
					 (unsigned int)size.width,
					 0,texture->format,GL_INT,NULL);
	  OGL_DEBUG(); break;
	case GL_TEXTURE_2D: glTexImage2D(texture->typetarget,0,texture->chan,
					 (unsigned int)size.width,
					 (unsigned int)size.height,
					 0,texture->format,GL_INT,NULL);
	  OGL_DEBUG(); break;
	case GL_TEXTURE_CUBE_MAP: glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+
					       cubeside,0,texture->chan,
					       (unsigned int)size.width,
					       (unsigned int)size.height,
					       0,texture->format,GL_INT,NULL);
	  OGL_DEBUG(); break;
	}
	texture->ubind();
      }
    }
  }

  RBGROUP::RBGROUP():updated(false){}
  RBGROUP::~RBGROUP(){}
}
#include "toluaxx.h"
namespace unfbo{
  
  bool RBGROUP::update(){
    if(updated){
      updated=false;
      return true;
    }
    return false;
  }
  RBGROUP::operator string(){
    string ret="";
    for(ITER i=begin();i!=end();i++){
      ret+=(*i).first+",";
    }
    ret.erase(ret.length()-1);
    return ret;
  }
  
  __GROUP_IMPLEMENTATION_(unfbo::RBGROUP,
                          unfbo::RENDERBUFFER,
                          ,
                          ,
			  );
  
}
