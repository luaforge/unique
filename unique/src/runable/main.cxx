#include"toluaxx.h"
#define UNMODULE(name) TOLUA_API int luaopen_ ## name (lua_State*);
#include"modules.hxx"
#undef UNMODULE

#include"unbase.hxx"
extern "C" {
#include"lualib.h"
}

#define UNMODULE(name) luaopen_ ## name (L);
int main(int argc,char** argv){
  lua_State* L=luaL_newstate();
  luaL_openlibs(L);
  cout<<"Engine inited...."<<endl;
  #include"modules.hxx"
  cout<<"Modules loaded...."<<endl;
  if(argc>1){
    luaL_loadfile(L,argv[1]);
    lua_call(L,0,2);
  }
  lua_close(L);
  cout<<"Engine closed...."<<endl;
}
#undef UNMODULE
