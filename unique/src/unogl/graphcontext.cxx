#include "graphcontext.hxx"
using namespace unogl;

PIXELMODE::PIXELMODE():red(8),green(8),blue(8),alpha(8),depth(24),stencil(8){}

const vec2 GRAPHCONTEXT::_320x240(320,240);
const vec2 GRAPHCONTEXT::_640x480(640,480);
const vec2 GRAPHCONTEXT::_800x600(800,600);
const vec2 GRAPHCONTEXT::_1024x768(1024,768);

GRAPHCONTEXT::GRAPHCONTEXT():CONTEXT(),buffering(2),osampling(0),sampling(2),size(320,240){}
GRAPHCONTEXT::~GRAPHCONTEXT(){}
// OpenGL
void GRAPHCONTEXT::bind(){}  // Binding context (similar make current)
void GRAPHCONTEXT::ubind(){} // Unbinding context (similar swap buffer or flush buffer)
void GRAPHCONTEXT::RendererInfo(){
  vendor    =(const char*)glGetString(GL_VENDOR);
  renderer  =(const char*)glGetString(GL_RENDERER);
  version   =(const char*)glGetString(GL_VERSION);
  extensions=(const char*)glGetString(GL_EXTENSIONS);
}
void GRAPHCONTEXT::InitExtensions(){
  glInitExtensions();
  //InitExtensionsLocal();
}
void GRAPHCONTEXT::clear(){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

GRAPHCONTEXT::operator string(){
  return "GRAPHCONTEXT{}";
}

KEYS::KEYS(){}
KEYS::~KEYS(){}
KEYS::ITER KEYS::begin(){
  return array.begin();
}
KEYS::ITER KEYS::end(){
  return array.end();
}
void KEYS::operator()(int&num,KEY*&key){
  num++;
  if(num>0&&num<array.size()){
    key=&array[num];
  }else if(num==array.size()){
    num=-1;
    key=NULL;
  }else{
    num=0;
    key=&array[num];
  }
}
const KEY* KEYS::operator[](int num){
  if(num>0&&num<=array.size())return &(array[num-1]);else return NULL;
}
void KEYS::clear(){
  array.clear();
}
KEYS::operator string(){
  string ret="{";
  for(ITER i=array.begin();i!=array.end();i++){ret+=static_cast<string>(*i)+",";}
  if(ret[ret.length()-1]==',')ret[ret.length()-1]='}';else ret+="}";
  return ret;
}
