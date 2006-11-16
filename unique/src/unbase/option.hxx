#pragma once
#include"platform.hxx"
#include<string>
#include<iostream>
using namespace std;
#define EL "\n"
#define EN "en_EN"
#define RU "ru_RU"

#define CLASSINFODECL static string __info(string);
#define CLASSINFO(class,cont) \
string class::__info(string l){ \
  cont \
  return string("Info unit for locale \"")+l+"\" not found!"; \
} // Class Info wraper
#define CLASSINFOENT(locale,contain) \
  if(l==#locale)return string(#contain); // Class Info Entire wraper

namespace unbase{//tolua_export
  // Action state message
  class STATE{//tolua_export
  public:
    //tolua_begin
    bool state;
    int   code;
    string msg;
    //tolua_end
  public:
    STATE(const char* s);
    STATE(bool v,const char* s);
    STATE(const char* s,bool v);
    //tolua_begin
    STATE();
    STATE(string);
    STATE(bool);
    STATE(bool,string);
    STATE(string,bool);
    ~STATE();
    operator string();
    static string __info(string);
    //tolua_end
  };//tolua_export
  
  inline std::ostream& operator<<(std::ostream& stm, STATE& err){return stm<<string(err);}
  class LOCALE{
  public:
    static string lang;
  public:
    static string convert(string source,string from,string to){
      if(to=="")to=lang;
    }
  };
  void unlua_try_load_node(void* self, string type, string key, string name, string code);
}//tolua_export

/*
 *  Optional defines
 *
 */

#define __GROUP_IMPLEMENTATION_(group_class,object_class,resource_type,group_create_luacode,object_create_luacode) \
  /* full hierarchy name */						\
  string group_class::fullhiername(string n){				\
    string r=name;							\
    if(n.length()>0){ if(r.length()>0)r+="."; r+=n; }			\
    if(parent){ r=parent->fullhiername(r); }				\
    return r;								\
  }									\
  /* iterator method */							\
  void group_class::operator()(string&k,object_class*&n){		\
    map<string,object_class*>::iterator i;				\
    if(k.length()>0){ i=pool.find(k); if(i!=pool.end())i++; }		\
    else i=pool.begin();						\
    if(i==pool.end()){ k=""; n=NULL; }					\
    else{ k=i->first; n=i->second; }					\
  }									\
  /* index method */							\
  object_class* group_class::get(string k){				\
    if(k.length()<=0)return NULL;					\
    if(pool.find(k)==pool.end() && autoload){				\
      string pn=fullhiername(k);					\
      RESOURCE r=resource(pn,#resource_type);				\
      if(r.type==RESOURCE::dir){					\
	string l=group_create_luacode;					\
	string b=#resource_type; b+=" `"; b+=pn; b+="` group script";	\
	unbase::unlua_try_load_node(this,#object_class,k,b,l);		\
      }else if(r.type==RESOURCE::stm){					\
	STREAM& s=r.stream(STREAM::inp);				\
	if(s.good()){							\
	  string l=object_create_luacode; l+=" "; l+=s.read();		\
	  string b=" `"; b+=pn; b+="` object script";			\
	  unbase::unlua_try_load_node(this,#object_class,k,b,l);	\
	}								\
      }									\
    }									\
    if(pool.find(name)==pool.end())return NULL;else return pool[name];	\
  }									\
  /* newindex method */							\
  void group_class::set(string k, object_class* o){			\
    if(k.length()<=0)return;						\
    if(pool.find(k)!=pool.end()){					\
      if(autoload){							\
	pool[k]->name="";						\
	pool[k]->parent=NULL;						\
      }									\
      pool.erase(k);							\
    }									\
    if(o){								\
      pool[k]=o;							\
      if(autoload){							\
	o->name=k;							\
	o->parent=this;							\
      }									\
    }									\
  }


