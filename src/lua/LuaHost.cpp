#include "LuaHost.hpp"

/*static int l_my_print(lua_State* L) {
  int nargs = lua_gettop(L);
  std::cout << "in my_print:";
  for (int i = 1; i <= nargs; ++i) {
    std::cout << lua_tostring(L, i);
  }
  std::cout << std::endl;

  return 0;
}

static const struct luaL_Reg printlib[] = {
    {"print", l_my_print}, {NULL, NULL}
};*/

LuaHost::LuaHost() : lua_state_() {
  lua_state_.open_libraries(sol::lib::base);

  sol::usertype<Player> player_type = lua_state_.new_usertype<Player>(
      "player", sol::constructors<Player(Atlas&, b2World&)>(), "set_rot",
      &Player::SetRot, "id", &Player::type_id_);

  // lua_state_.script("print(pl.id)");
}

string LuaHost::Script(const string& lua_code) {
  auto result = lua_state_.safe_script(lua_code, sol::script_pass_on_error);

  if (!result.valid()) {
    sol::error err = result;
    return err.what();
  } else {
    return result;
  }
}

sol::state& LuaHost::GetState() { return lua_state_; }

LuaHost::~LuaHost() {}
