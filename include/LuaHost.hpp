#ifndef LUAHOST_H
#define LUAHOST_H

#include <iostream>
#include <lua.hpp>
#include <sol/sol.hpp>
#include <string>

#include "Player.hpp"

using std::string;

class LuaHost {
 public:
  LuaHost();

  string Script(const string& lua_code);

  sol::state& GetState();

  ~LuaHost();

  void printError(const string& variableName, const string& reason);
  sol::state lua_state_;
  int level = 0;
};

#endif  // LUAHOST_H
