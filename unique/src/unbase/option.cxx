#include"option.hxx"
using namespace unbase;

STATE::STATE():state(true),msg("Message empty!"){}
STATE::STATE(string s):state(false),msg(s){}
STATE::STATE(const char* s):state(false),msg(s){}
STATE::STATE(bool v):state(v),msg("Fatal error!"){}
STATE::STATE(bool v,string s):state(v),msg(s){}
STATE::STATE(bool v,const char* s):state(v),msg(s){}
STATE::STATE(string s,bool v):state(v),msg(s){}
STATE::STATE(const char* s,bool v):state(v),msg(s){}
STATE::~STATE(){}

STATE::operator string(){return state?string("Normal: ")+msg:string("Error: ")+msg;}

unsigned long address(void* obj){
  return (unsigned int)obj;
}
