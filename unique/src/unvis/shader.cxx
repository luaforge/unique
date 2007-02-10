/***************************************************************************
 *            shader.cpp
 *
 *  Wed Jun 29 17:12:37 2005
 *  Copyright  2005  Fenix
 *  tonder@trktvs.ru
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include"shader.hxx"
#include"undata.hxx"

#include"texture.hxx"

#include<toluaxx.h>

namespace unvis{
  using namespace unbase;
  using namespace undata;
  using namespace unogl;
  
  SHADER::operator string(){
    return "SHADERPROG{}";
  }
  
  SHDGROUP::SHDGROUP():SHADER(),autoload(false){}
  SHDGROUP::SHDGROUP(bool al):SHADER(),autoload(al){}
  SHDGROUP::~SHDGROUP(){}
  
  __GROUP_IMPLEMENTATION_(unvis::SHDGROUP,
			  unvis::SHADER,
			  __GROUP_HIER_TRY_GET_CXXCODE_(unvis::SHDGROUP,
							unvis::SHADER,
							shader,
							"return unvis.SHDGROUP(true)",
							"local SHADER=unvis.SHADER\n"
							"local sint=unvis.sint\n"
							"local GLSLPROG=unvis.GLSLPROG\n"
							"local GLSLVERT=unvis.GLSLVERT\n"
							"local GLSLFRAG=unvis.GLSLFRAG"
							),
			  __GROUP_HIER_SET_CXXCODE_(),
			  __GROUP_HIER_DEL_CXXCODE_()
			  );

  void SHDGROUP::chautoload(bool al){
    for(ITER i=begin();i!=end();i++)chautoload(al);
    autoload=al;
  }

  bool SHDGROUP::update(){
    for(ITER i=begin();i!=end();i++){
      i->second->update();
    }
  }

  SHDGROUP::operator string(){
    string r="SHDGROUP{";
    int t=r.length();
    for(ITER i=pool.begin();i!=pool.end();i++){
      r+=(*i).first+",";
    }
    if(t>r.length())r.erase(r.length()-1);
    r+="}";
    return r;
  }
  
  GLSLUNIFORM::GLSLUNIFORM(GLSLPROG* o):prog(o){}
  GLSLUNIFORM::~GLSLUNIFORM(){}
# define GET_MACROS(glvar,glfunc,gltype,gldef,glret) {			\
    glvar glret;							\
    glUseProgram(prog->obj);						\
    int param;								\
    if((param=prog->uniformlocation(name))>=0){				\
      if(type.find(name)!=type.end()){					\
	glfunc;								\
      }else{								\
	ret=gldef;							\
      }									\
    }else{								\
      ret=gldef;							\
    }									\
    glUseProgram(0);							\
    OGL_DEBUG();							\
    return glret;							\
  }
  void GLSLUNIFORM::getbool(string name, bool* ret)
    GET_MACROS(,glGetUniformiv(param,1,(GLint*)ret);nobool=!ret,BOOL,&nobool,);
  void GLSLUNIFORM::getscal(string name,float* ret)
    GET_MACROS(,glGetUniformfv(param,1,ret);noscal=*ret+0.1,SCAL,&noscal,);
  /*
  sint* GLSLUNIFORM::getsint(string name)GET_MACROS(sint,glGetUniformiv(param, 1,ret),SINT,NULL,&ret);
  vec2* GLSLUNIFORM::getvec2(string name)GET_MACROS(vec2,glGetUniformfv(param, 2,ret),VEC2,NULL,&ret);
  vec3* GLSLUNIFORM::getvec3(string name)GET_MACROS(vec3,glGetUniformfv(param, 3,ret),VEC3,NULL,&ret);
  vec4* GLSLUNIFORM::getvec4(string name)GET_MACROS(vec4,glGetUniformfv(param, 4,ret),VEC4,NULL,&ret);
  mat3* GLSLUNIFORM::getmat3(string name)GET_MACROS(mat3,glGetUniformfv(param, 9,ret),MAT3,NULL,&ret);
  mat4* GLSLUNIFORM::getmat4(string name)GET_MACROS(mat4,glGetUniformfv(param,16,ret),MAT4,NULL,&ret);
  */
# define SET_MACROS(glfunc,gltype) {					\
    glUseProgram(prog->obj);						\
    int param;								\
    if((param=prog->uniformlocation(name))>=0){				\
      glfunc;								\
      OGL_DEBUG();							\
      cout<<"Set shader uniform[\""<<name<<"\"]="<<gltype<<endl;	\
      type[name]=gltype;						\
    }									\
    glUseProgram(0);							\
    OGL_DEBUG();							\
  }
  void GLSLUNIFORM::setbool(string name, bool   value)SET_MACROS(glUniform1i(param,value),BOOL);
  void GLSLUNIFORM::setsint(string name, sint&  value)SET_MACROS(glUniform1i(param,value()),SINT);
  void GLSLUNIFORM::setscal(string name, scalar value)SET_MACROS(glUniform1f(param,value),SCAL);
  void GLSLUNIFORM::setvec2(string name, vec2&  value)SET_MACROS(glUniform2fv(param,1,value),VEC2);
  void GLSLUNIFORM::setvec3(string name, vec3&  value)SET_MACROS(glUniform3fv(param,1,value),VEC3);
  void GLSLUNIFORM::setvec4(string name, vec4&  value)SET_MACROS(glUniform4fv(param,1,value),VEC4);
  void GLSLUNIFORM::setmat3(string name, mat3&  value)SET_MACROS(glUniformMatrix3fv(param,1,GL_FALSE,value),MAT3);
  void GLSLUNIFORM::setmat4(string name, mat4&  value)SET_MACROS(glUniformMatrix4fv(param,1,GL_FALSE,value),MAT4);
  void GLSLUNIFORM::setnull(string name, void* value){
    if(value!=NULL)return;
    if(type.find(name)!=type.end())type.erase(name);
  }
  GLSLUNIFORM::operator string(){return "UNIFORM()";}
  
  GLSLSHADER::GLSLSHADER():SHDCHUNK(){}
  GLSLSHADER::GLSLSHADER(string s):SHDCHUNK(),src(s){}
  GLSLSHADER::GLSLSHADER(string s,string t):SHDCHUNK(),src(s),text(t){}
  GLSLSHADER::~GLSLSHADER(){if(obj)glDeleteShader(obj);}
  bool GLSLSHADER::update(){
    bool t=otext!=text,s=osrc!=src;
    if(t||s){
      if(s&&!t){ // if changed source only then reload source
	load();
	compile();
	param();
	otext=text;
	osrc=src;
      }else{ // if changed text (source may be changed too)
	compile();
	param();
	otext=text;
	osrc=src;
      }
      return true;
    }else return false;
  }
  bool GLSLSHADER::load(){
    RESOURCE r;
    //if(parent)r=undata::resource(parent->fullhiername(src),"shaderdata");
    if(r.type!=RESOURCE::stm)r=undata::resource(src,"shaderdata");
    if(r.type==RESOURCE::stm&&r.access&STREAM::inp){
      STREAM& s=r.stream();
      text=s.read();
      r.stream(s);
      return true;
    }return false;
  }
  bool GLSLSHADER::compile(){
    GLint nreturn; // Return state
    const GLchar* source=text.data();
    glShaderSource(obj,1,&source,NULL);
    glCompileShader(obj);
    glGetShaderiv(obj,GL_COMPILE_STATUS,&nreturn);
    if(nreturn){
      state=STATE(src+" compiled ok",true);
    }else{
      GLchar str[4096];
      GLsizei len=0;
      glGetShaderInfoLog(obj,strlen(str),&len,str);
      str[len]='\0';
      state=STATE(src+"\n"+string(str),false);
    }
    OGL_DEBUG();
    return bool(nreturn);
  }
  bool GLSLSHADER::param(){
    GLuint i=0,j=0,k=0;
    for(;i<text.length();){
      i=text.find("uniform",i);
      if(i==string::npos)break;
      i=text.find(" ",i);
      i=text.find(" ",++i);
      j=text.find(";",++i);
      string name=text.substr(i,j-i);
      uniform[name]=0;
      //cout<<"["<<text.substr(i,j-i)<<"]"<<endl;
    }
  }
  GLSLSHADER::operator string(){return string("GLSLSHADER(\"")+src+"\",\""+text+"\")";}
  
  GLSLVERT::GLSLVERT():GLSLSHADER(){obj=glCreateShader(GL_VERTEX_SHADER);}
  GLSLVERT::GLSLVERT(string s):GLSLSHADER(s){obj=glCreateShader(GL_VERTEX_SHADER);}
  GLSLVERT::GLSLVERT(string s,string t):GLSLSHADER(s,t){obj=glCreateShader(GL_VERTEX_SHADER);}
  GLSLVERT::~GLSLVERT(){glDeleteShader(obj);}
  GLSLVERT::operator string(){return string("GLSLVERT(\"")+src+"\",\""+text+"\")";}

  GLSLFRAG::GLSLFRAG():GLSLSHADER(){obj=glCreateShader(GL_FRAGMENT_SHADER);}
  GLSLFRAG::GLSLFRAG(string s):GLSLSHADER(s){obj=glCreateShader(GL_FRAGMENT_SHADER);}
  GLSLFRAG::GLSLFRAG(string s,string t):GLSLSHADER(s,t){obj=glCreateShader(GL_FRAGMENT_SHADER);}
  GLSLFRAG::~GLSLFRAG(){glDeleteShader(obj);}
  GLSLFRAG::operator string(){return string("GLSLFRAG(\"")+src+"\",\""+text+"\")";}
  
  GLSLSHADER* GLSLPROG::get(string k){
    return attached(k);
  }
  void GLSLPROG::set(string k, GLSLSHADER* n){
    detach(k); attach(k,n); update();
  }

  GLSLPROG::GLSLPROG():SHADER(),state(),uniform(this){obj=glCreateProgram();}
  GLSLPROG::~GLSLPROG(){glDeleteProgram(obj);}
  void GLSLPROG::bind(){update();glUseProgram(obj);binddefaultparameters();}
  void GLSLPROG::ubind(){glUseProgram(0);}
  bool GLSLPROG::detach(string i){
    if(pool.find(i)==pool.end())return false;
    if(pool[i]!=NULL)glDetachShader(obj,pool[i]->obj);
    OGL_DEBUG();
    pool.erase(i);
    return true;
  }
  bool GLSLPROG::attach(string i,GLSLSHADER* s){
    upd=true;
    pool[i]=s;
    glAttachShader(obj,s->obj);
    OGL_DEBUG();
    state=STATE(true,string("attach"));
    return true;
  }
  GLSLSHADER* GLSLPROG::attached(string i){
    if(pool.find(i)==pool.end())return NULL;
    return pool[i];
  }
  bool GLSLPROG::link(){
    GLchar str[4096];
    GLint nreturn;
    defaultattribs();
    glLinkProgram(obj);
    glGetProgramiv(obj,GL_LINK_STATUS,&nreturn);
    if(!nreturn){
      glGetProgramInfoLog(obj,sizeof(str),NULL,str);
      state=STATE(string("GLSLPROG: Link error: \n")+str,false);
      return false;
    }
    OGL_DEBUG();
    glValidateProgram(obj);
    glGetProgramiv(obj,GL_VALIDATE_STATUS,&nreturn);
    if(!nreturn){
      glGetProgramInfoLog(obj,sizeof(str),NULL,str);
      state=STATE(string("GLSLPROG: SetParameter error: \n")+str,false);
      return false;
    }
    OGL_DEBUG();
    glGetProgramInfoLog(obj,sizeof(str),NULL,str);
    state=STATE(string("GLSLPROG: LinkedInfo: \n")+str,true);
    OGL_DEBUG();
    defaultparameters();
    OGL_DEBUG();
    return true;
  }

  bool GLSLPROG::update(){
    for(ITER i=pool.begin();i!=pool.end();i++)if(i->second)if(i->second->update())upd=true;
    if(upd)link();
    upd=false;
    return true;
  }
  void GLSLPROG::defaultparameters(){
    glUseProgram(obj);
    GLint par_unit=0;
    for(unsigned char i=0;i<8;i++){
      char tex_name[16];
      sprintf(tex_name,"gl_TexUnit_%d",i);
      if((par_unit=glGetUniformLocation(obj,tex_name))>=0){
	glUniform1i(par_unit, i);
      }
    }
    OGL_DEBUG();
    if((par_unit=glGetUniformLocation(obj,"gl_TexUnit"))>=0){
      const GLint tex_units[4]={0,1,2,3};
      glUniform1iv(par_unit,4,tex_units);
    }
    OGL_DEBUG();
    if((par_unit=glGetUniformLocation(obj,"glViewport"))>=0){
      int vp[4];
      glGetIntegerv(GL_VIEWPORT,vp);
      glUniform1iv(par_unit,4,vp);    
    }
    OGL_DEBUG();
    if((par_unit=glGetUniformLocation(obj,"glViewportTexCompatSize"))>=0){
      int vp[4];
      glGetIntegerv(GL_VIEWPORT,vp);
      vp[0]=glTextureCompatSize(vp[2]);
      vp[1]=glTextureCompatSize(vp[3]);
      glUniform1iv(par_unit,2,vp);
    }
    if((par_unit=glGetUniformLocation(obj,"glViewport2TextureCoeff"))>=0){
      int vp[4];
      glGetIntegerv(GL_VIEWPORT,vp);
      vp[0]=glTextureCompatSize(vp[2]);
      vp[1]=glTextureCompatSize(vp[3]);
      vec2 c=vec2(scalar(vp[2])/scalar(vp[0]),scalar(vp[3])/scalar(vp[1]));
      glUniform2fv(par_unit,1,c);
    }
    OGL_DEBUG();
    /*
    
    GLint p=0;
    if((p=glGetUniformLocation(obj,"diffusemap"))>=0)  glUniform1i(p,0);
    if((p=glGetUniformLocation(obj,"ambientmap"))>=0)  glUniform1i(p,1);
    if((p=glGetUniformLocation(obj,"normalmap"))>=0)   glUniform1i(p,1);
    if((p=glGetUniformLocation(obj,"heightmap"))>=0)   glUniform1i(p,2);
    if((p=glGetUniformLocation(obj,"spacularmap"))>=0) glUniform1i(p,2);
    if((p=glGetUniformLocation(obj,"emissionmap"))>=0) glUniform1i(p,3);
    if((p=glGetUniformLocation(obj,"detailmap"))>=0)   glUniform1i(p,3);
    OGL_DEBUG();
    */
#ifdef SESHADER_FAST_UNIFORM
    for(GLuint s=0;s<array.size();s++){
      for(GLSLSHADER::UNIFORM::iterator i=array[s]->uniform.begin();i!=array[s]->uniform.end();i++){
	(*i).second=glGetUniformLocation(obj,(*i).first.data());
	//assert((*i).second >= 0);
      }
    }
#endif
    OGL_DEBUG();
    glUseProgram(0);
  }
  void GLSLPROG::defaultattribs(){
    // Numbered vertex attribs
    glBindAttribLocation(obj, 0,"glVertexAttrib0");
    glBindAttribLocation(obj, 1,"glVertexAttrib1");
    glBindAttribLocation(obj, 2,"glVertexAttrib2");
    glBindAttribLocation(obj, 3,"glVertexAttrib3");
    glBindAttribLocation(obj, 4,"glVertexAttrib4");
    glBindAttribLocation(obj, 5,"glVertexAttrib5");
    glBindAttribLocation(obj, 6,"glVertexAttrib6");
    glBindAttribLocation(obj, 7,"glVertexAttrib7");
    glBindAttribLocation(obj, 8,"glVertexAttrib8");
    glBindAttribLocation(obj, 9,"glVertexAttrib9");
    glBindAttribLocation(obj,10,"glVertexAttrib10");
    glBindAttribLocation(obj,11,"glVertexAttrib11");
    glBindAttribLocation(obj,12,"glVertexAttrib12");
    glBindAttribLocation(obj,13,"glVertexAttrib13");
    glBindAttribLocation(obj,14,"glVertexAttrib14");
    glBindAttribLocation(obj,15,"glVertexAttrib15");
    OGL_DEBUG();
    // Named vertex attribs
    glBindAttribLocation(obj,12,"glTangent");  // Tangent  vector
    glBindAttribLocation(obj,13,"glBinormal"); // Binormal vector
    glBindAttribLocation(obj,14,"glNormal");   // Normal   vector
    OGL_DEBUG();
    glBindAttribLocation(obj,12,"glTangentMatrix"); // Tangent matrix
    glBindAttribLocation(obj,13,"glTangentMatrix");
    glBindAttribLocation(obj,14,"glTangentMatrix");
    OGL_DEBUG();
    //cout<<"gl_Vertex = "<<glGetAttribLocation(obj,"gl_Vertex")<<endl;
  }
#define SET_PARAM_VALUE(name,func,count,value) {GLuint p=0;if((p=glGetUniformLocation(obj,#name))>=0)func(p,count,value);}
  void GLSLPROG::binddefaultparameters(){
    SET_PARAM_VALUE(glLights,glUniform1iv,1,&gl_Lights());
    SET_PARAM_VALUE(glCameraPos,glUniform3fv,1,gl_CameraPosition());
    int vp[4];
    glGetIntegerv(GL_VIEWPORT,vp);
    SET_PARAM_VALUE(glViewport,glUniform4iv,1,vp);
  }
  GLint GLSLPROG::uniformlocation(string name){
#ifdef SESHADER_FAST_UNIFORM
    for(GLuint s=0;s<array.size();s++){
      GLSLSHADER::UNIFORM::iterator i=array[s]->uniform.find(name);
      if(i!=array[s]->uniform.end())return (*i).second;
      //GLint i=array[s]->uniform[name];
      //if(i)return array[s]->uniform[name];
    }
#else
    return glGetUniformLocation(obj,name.data());
#endif
  }

  GLSLPROG::operator string(){return string("GLSLPROG(")+")";}
  
}
