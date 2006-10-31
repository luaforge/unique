#include"toluaxx.h"
#define UNMODULE(name) TOLUA_API int luaopen_ ## name (lua_State*);
#include"modules.hxx"
#undef UNMODULE

#define UNMODULE(name) luaopen_ ## name (L);
TOLUA_API int luaopen_lunique(lua_State* L){
  #include"modules.hxx"
}
#undef UNMODULE
