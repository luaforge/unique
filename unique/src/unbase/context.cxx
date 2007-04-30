#include"context.hxx"
using namespace unbase;

CONTEXT::CONTEXT():vendor("{None}"),renderer("{null}"),version("{none}"),extensions("{not found}"){}
CONTEXT::~CONTEXT(){}
bool CONTEXT::open(){}
void CONTEXT::close(){}
void CONTEXT::bind(){}
void CONTEXT::ubind(){}
void CONTEXT::RendererInfo(){}
void CONTEXT::clear(){}
CONTEXT::operator string(){return "CONTEXT()";}

CONTEXTS::CONTEXTS(){}
CONTEXTS::~CONTEXTS(){}
void CONTEXTS::operator()(string&n,CONTEXT*&c){
  ITER i;
  if(n==""){
    i=array.begin();
  }else{
    i=array.find(n);
    if(i==array.end()){n="";c=NULL;return;}
    i++; for(;i->second==NULL&&i!=array.end();i++);
    if(i==array.end()){n="";c=NULL;return;}
  }
  n=i->first;c=i->second;return;
}
/*
CONTEXT* &CONTEXTS::operator[](string name){
  //if(node)array.insert(std::make_pair(name,node));
  //else array.erase(name);
  return array[name];
}
*/
CONTEXT* CONTEXTS::get(string n){
  if(array.find(n)!=array.end()) return array[n];
  return NULL;
}
void CONTEXTS::set(string n, CONTEXT* c){
  if(c==NULL)return;
  array[n]=c;
}
CONTEXTS::operator string(){
  string ret="{";
  for(ITER i=array.begin();i!=array.end();i++){
    if(!i->second)continue;
    ret+=(*i).first+"="+static_cast<string>(*(*i).second)+",";
  }
  if(ret[ret.length()-1]==',')ret[ret.length()-1]='}';else ret+="}";
  return ret;
}
