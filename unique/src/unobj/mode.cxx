#include"mode.hxx"

namespace unobj{
  MODE::MODE():geom(true),matl(true),name(true),axis(false),modl(false),link(false),quer(true),shad(true){}
  MODE::MODE(bool m){for(int i=0;i<__end_-__begin_;i++)array[i]=m;}
  
  MODE::operator string(){
    string r; {char b[16]; sprintf(b,"%d",__end_-__begin_); r+=b; } return r;
  }
  
  bool& MODE::operator[](int i){
    i=i>0?i:0;
    i=i<__end_-__begin_?i:__end_-__begin_;
    return array[i];
  }
  
  MODE MODE::operator()(const MODE& s, const MODE& m)const{
    MODE r;
    for(int i=0;i<__end_-__begin_;i++)r.array[i]=s.array[i]?m.array[i]:array[i];
    return r;
  }
  int MODE::operator~(){
    return __end_-__begin_;
  }
}
