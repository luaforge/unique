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
