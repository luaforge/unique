#include"toluaxx.h"
#define UNMODULE(name) TOLUA_API int luaopen_ ## name (lua_State*);
#include"modules.hxx"
#undef UNMODULE

#define UNMODULE(name) luaopen_ ## name (L);
int main(int argc,char** argv){
  lua_State* L=lua_open();
  #include"modules.hxx"
  if(argc>2){
    luaL_loadfile(L,argv[1]);
    lua_call(L,0,2);
  }
  lua_close(L);
}
#undef UNMODULE
