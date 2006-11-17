#include"option.hxx"

namespace unbase{
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
  
  MULTNAME::MULTNAME(string s){parse(s);}
  void MULTNAME::operator()(string s){parse(s);}
  string MULTNAME::operator()(int i){return cnstr(i);}
  int MULTNAME::operator~(){return name.size();}
  MULTNAME::operator string(){return cnstr();}
  string& MULTNAME::operator[](int i){
    i=i==0?1:i;
    i=i<0?name.size()+i:i-1;
    i=i>(name.size()-1)?(name.size()-1):i;
    return name[i];
  }
  void MULTNAME::parse(string s){
    if(s.length()<=0)return;
    int a,b;
    name.clear();
    if((a=s.find("{"))<s.length()){
      if((b=s.find("}",a+1))<s.length()){
	prefix=s.substr(0,a);
	suffix=s.substr(b+1);
	string n=s.substr(a+1,b-a-1);
	for(a=0;(b=n.find(",",a))<n.length();a=b+1){
	  name.push_back(n.substr(a,b-a));
	}
	name.push_back(n.substr(a,b-a));
      }
    }
    if(s.length()>0 && name.size()<=0 && suffix.length()<=0 && prefix.length()<=0)prefix=s;
  }
  string MULTNAME::cnstr(int i){
    string r=prefix;
    if(i==0){
      if(name.size()>0){
	r+="{";
	for(int i=0;i<name.size();i++){
	  r+=name[i];
	  if(i<name.size()-1)r+=",";
	}
	r+="}";
      }
    }else{
      i=i<0?name.size()+i:i-1;
      i=i>(name.size()-1)?(name.size()-1):i;
      r+=name[i];
    }
    r+=suffix;
    return r;
  }
  
  unsigned long address(void* obj){
    return (unsigned int)obj;
  } 
}

#include<toluaxx.h>

namespace unbase{
  void unlua_try_load_node(void* self, string type, string key, string name, string code){
    string l="tolua.proxy.set('.__node_load_func_',function() "+code+" end)";
    
    lua_State* L=tolua_state();
    int __top_=lua_gettop(L);

    int s=luaL_loadbuffer(L,l.data(),l.length(),name.data()); /* stack: buf */
    if(s!=0)lua_error(L);
    if(!lua_gettop(L)==__top_+1 || !lua_isfunction(L,__top_+1))return;
    tolua_proxypush(L);
    lua_call(L,0,0);                                 /* stack: */
    lua_pushstring(L,".__node_load_func_");          /* stack: param_name */
    tolua_getproxy(L,-1);                            /* stack: node_load_func */
    tolua_proxypop(L);
    if(!lua_gettop(L)==__top_+1 || !lua_isfunction(L,__top_+1))return;
    lua_call(L,0,1);                                 /* stack: obj */
    if(!lua_gettop(L)==__top_+1 || !lua_isuserdata(L,__top_+1))return;
    tolua_pushusertype(L,self,type.data());          /* stack: obj root */
    lua_insert(L,-2);                                /* stack: root obj */
    lua_pushstring(L,key.data());                    /* stack: root obj name */
    lua_insert(L,-2);                                /* stack: root name obj */
    lua_settable(L,-3);                              /* stack: root */
    lua_remove(L,-1);                                /* stack: */
  }
}
