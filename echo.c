#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main(int argc, char **argv) {
  lua_State *l;
  l = luaL_newstate();
  luaL_openlibs(l);
  lua_newtable(l);
  for (int i = 1; i <= argc; ++i) {
    lua_pushinteger(l, i);
    lua_pushstring(l, argv[i - 1]);
    lua_settable(l, -3);
  }
  lua_setglobal(l, "c_argv");
  if (luaL_dofile(l, "echo.lua") != LUA_OK) {
    printf("dofile error: %s\n", lua_tostring(l, -1));
    return 1;
  }
  lua_close(l);
  return 0;
}
