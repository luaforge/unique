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
}//tolua_export
