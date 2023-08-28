#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <dirent.h>

#define MAX_DIRS 1000

lua_State *l;

/*
  struct dirent
  {
  #ifndef __USE_FILE_OFFSET64
  __ino_t d_ino;
  __off_t d_off;
  #else
  __ino64_t d_ino;
  __off64_t d_off;
  #endif
  unsigned short int d_reclen;
  unsigned char d_type;
  char d_name[256];
  };
*/

DIR *opened_dirs[MAX_DIRS];
int idx = 0;

int c_opendir(lua_State *l) {
  int arg_cnt = lua_gettop(l);
  if (arg_cnt != 1) {
    lua_pushnil(l);
    return 1;
  }
  const char *path = lua_tostring(l, -1);
  int index = idx;  
  opened_dirs[idx++] = opendir(path);
  lua_newtable(l);
  int cnt = 1;
  struct dirent *entry;
  while ((entry = readdir(opened_dirs[idx - 1])) != NULL) {
    lua_pushinteger(l, cnt++);
    lua_pushstring(l, entry->d_name);
    lua_settable(l, -3);
  }
  lua_pushinteger(l, index);
  return 2;
}

int c_closedir(lua_State *l) {
  if (lua_gettop(l) != 1) {
    lua_pushnil(l);
    return 1;
  }

  int index = lua_tointeger(l, -1);
  if (index < 0 || index > idx) {
    lua_pushboolean(l, 0);
    return 1;
  }
  if(closedir(opened_dirs[index]) == 0)
    lua_pushboolean(l, 1);
  else
    lua_pushboolean(l, 0);
  return 1;
}

void set_argv(int argc, char** argv) {
  lua_newtable(l);
  for (int i = 1; i <= argc; ++i) {
    lua_pushinteger(l, i);
    lua_pushstring(l, argv[i - 1]);
    lua_settable(l, -3);
  }
  lua_setglobal(l, "c_argv");
}

int main(int argc, char **argv) {
  l = luaL_newstate();
  luaL_openlibs(l);
  set_argv(argc, argv);
  lua_register(l, "opendir", c_opendir);
  lua_register(l, "closedir", c_closedir);
  luaL_dofile(l, "ls.lua");
  lua_close(l);
  return 0;
}
