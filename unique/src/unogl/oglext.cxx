
#define NOT_EXTERN_EXTENSIONS
#include"oglext.hxx"

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

// Common extensions synonyms
// MipMap
PFNGLGENERATEMIPMAPEXTPROC          glGenerateMipmap         =glGenerateMipmapEXT;
// Renderbuffer
PFNGLGENRENDERBUFFERSEXTPROC        glGenRenderbuffers       =glGenRenderbuffersEXT;
PFNGLDELETERENDERBUFFERSEXTPROC     glDeleteRenderbuffers    =glDeleteRenderbuffersEXT;
PFNGLRENDERBUFFERSTORAGEEXTPROC     glRenderbufferStorage    =glRenderbufferStorageEXT;
PFNGLBINDRENDERBUFFEREXTPROC        glBindRenderbuffer       =glBindRenderbufferEXT;
// Framebuffer
PFNGLGENFRAMEBUFFERSEXTPROC         glGenFramebuffers        =glGenFramebuffersEXT;
PFNGLDELETEFRAMEBUFFERSEXTPROC      glDeleteFramebuffers     =glDeleteFramebuffersEXT;
PFNGLBINDFRAMEBUFFEREXTPROC         glBindFramebuffer        =glBindFramebufferEXT;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC    glFramebufferTexture1D   =glFramebufferTexture1DEXT;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC    glFramebufferTexture2D   =glFramebufferTexture2DEXT;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC    glFramebufferTexture3D   =glFramebufferTexture3DEXT;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbuffer=glFramebufferRenderbufferEXT;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC  glCheckFramebufferStatus =glCheckFramebufferStatusEXT;

OGLEXT::OGLEXT():vendor("undefined"),renderer("software"),version("1.1.2"),extensions(""){}
OGLEXT::~OGLEXT(){}

void OGLEXT::Init(){// Инициализатор расширений
  /* Наше расширение - массив имен */
  glInitNamesArray(); // Инициализируем массив имен свободными значениями
  vendor=(const char*)glGetString(GL_VENDOR);
  renderer=(const char*)glGetString(GL_RENDERER);
  version=(const char*)glGetString(GL_VERSION);
  extensions=(const char*)glGetString(GL_EXTENSIONS);
  // Функции расширений
  // Вот так вот широко пришлось развернуться
#ifdef _WIN32_
  
  // По сути эти функции обеспечивают полную поддержку GLSL (GL Shading Language) 1 версии
  
#endif
}

bool OGLEXT::CheckGLError(const char* srcfile, 
			  const int srcline, 
			  const char* funcname){
  int errcode=glGetError();
  if(errcode){
    //Luna<OGLEXT>::msg("$gl_error_report",errcode,(const char*)gluErrorString(errcode),srcfile,srcline);
    //Luna<OGLEXT>::msg("$NL");
    printf("OpenGL error:%d (%s) in file \"%s\" line:%d\n",errcode,(const char*)gluErrorString(errcode),srcfile,srcline);
    return true;
  }
  return false;
}

void OGLEXT::gl_error(int& errcode, std::string& errname){
  errcode=glGetError();
  if(errcode){
    errname=(const char*)gluErrorString(errcode);
  }
}

/* В OpenGL не предусмотрена генерация имен, дорабатываем   */
/* 0 (ноль) - зарезервированное имя, при попадании объекты  */
/* с ним не рассматриваются и игнорируются при выделении     */
/* Если значение при индексе массива имен true - имя занято */
#include <math.h>
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
