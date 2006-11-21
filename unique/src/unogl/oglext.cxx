
#include"oglext.hxx"

namespace unogl{
  
  quat rotcameraquat;
  vec3 poscameravect;
  mat4 rotprojmat;
  mat4 rotprojmatinv;
  mat4 trnprojmat;
  mat4 trnprojmatinv;
  GLint maxlights;
  vec3& gl_CameraPosition(){return poscameravect;}
  quat& gl_CameraRotation(){return rotcameraquat;}
  mat4& gl_RotateProjectionMatrix(){return rotprojmat;}
  mat4& gl_RotateProjectionMatrixInv(){return rotprojmatinv;}
  mat4& gl_TranslateProjectionMatrix(){return trnprojmat;}
  mat4& gl_TranslateProjectionMatrixInv(){return trnprojmatinv;}
  GLint& gl_Lights(){return maxlights;}

  glExtFuncPtr glGetProcAddress(const char* name){
    glExtFuncPtr address;
#   if _WIN32 || _MINGW
    address=(glExtFuncPtr)wglGetProcAddress(name);
#   endif
#   if _LINUX
    address=(glExtFuncPtr)glXGetProcAddress((const GLubyte*)name);
#   endif
    if(address) return address;
    else cout<<"Warning: Extension `"<<name<<"` not found...."<<endl;
    return NULL;
  }
  
  // Define OpenGL extensions
# define GLEXT_FUNC(name,type,real) PFN##type##PROC name;
# include"oglext.func.hxx"
# undef GLEXT_FUNC

  // Initialize OpenGL extensions
# define GLEXT_FUNC(name,type,real) name=(PFN##type##PROC)glGetProcAddress(#real);
  void glInitExtensions(){
    cout<<"Init OpenGL extensions...."<<endl;
    glInitNamesArray();
#   include"oglext.func.hxx"
  }
# undef GLEXT_FUNC

  bool glCheckError(const char* srcfile, const int srcline){
    int errcode=glGetError();
    if(errcode){
      cout<<"OpenGL error:"<<errcode<<" ("<<(const char*)gluErrorString(errcode)<<") in file \""<<srcfile<<"\" line:"<<srcline<<endl;
      return true;
    }
    return false;
  }
}

#include <cmath>
namespace unogl{
#define GL_NAMES_ARRAY_SIZE 16777216
  static bool glnamesinited=false;
  //(unsigned int)(pow(2, sizeof(GLuint)*8)-1)
  static bool glNames[GL_NAMES_ARRAY_SIZE]; // Массив имен
  void glInitNamesArray(){ // Инициализация массива имен
    //printf("Names:%d\n", );
    if(!glnamesinited){
      for(GLuint i=0; i<GL_NAMES_ARRAY_SIZE; i++){ glNames[i]=false; }
      glnamesinited=true;
    }
  }
  void glGenNames(GLsizei n, GLuint* names){ // Генерация новых имен
    GLuint i=1,j=0;
    for(i=1,j=0; i<GL_NAMES_ARRAY_SIZE && j<n; i++){
      if(glNames[i]==false){ glNames[i]=true; names[j]=i; j++; }
    }
  }
  void glDeleteNames(GLsizei n, const GLuint* names){ // Освобождение сгенерированных имен
    for(GLuint j=0; j<n; j++){
      glNames[names[j]]=false;
      //names[j]=0;
    }
  }
  
  //glEnable(GL_BLEND); 
  //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 
  //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
}
