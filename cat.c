#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void l_pushargtotable(lua_State *l, int idx, char *s) {
  lua_pushinteger(l, idx);// push idx
  lua_pushstring(l, s); // push value.
  lua_settable(l, -3);
  //lua_rawseti(l, -2, idx);
}

int main(int argc, char **argv) {
  lua_State *l;
  l = luaL_newstate();
  luaL_openlibs(l);
  lua_newtable(l); // create a new table to store cmd args.
  for (int i = 0; i < argc; ++i){
    l_pushargtotable(l, i + 1, argv[i]); // idx starts from 1
  }
  lua_setglobal(l, "c_argv");
  if (!(luaL_dofile(l, "cat.lua") == LUA_OK)){
    printf("dofile failed: ");
    printf("%s\n", lua_tostring(l, -1));
  }
  lua_close(l);
  return 0;
}
