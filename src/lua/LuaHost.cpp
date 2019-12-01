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

LuaHost::LuaHost()
    : lua_state_(),
      script_queue_(),
      result_queue_(),
      cv_(),
      script_mutex_(),
      result_mutex_(),
      kill_lua_thread_(false),
      thread_done_(false),
      lua_thread_(&LuaHost::Execute, this) {
  lua_state_.open_libraries(sol::lib::base);

  sol::usertype<Player> player_type = lua_state_.new_usertype<Player>(
      "player", sol::constructors<Player(Atlas&, b2World&)>(),
      "set_rot", &Player::SetRot,
      "get_rot", &Player::GetRot,
      "set_pos", sol::resolve<void(float, float)>(&Player::SetPos),
      "get_pos", &Player::GetPos,
      "set_vel", sol::resolve<void(float, float)>(&Player::SetVel),
      "get_vel", &Player::GetVel,
      "apply_force", &Player::ApplyForce,
      "set_current_texture", &Player::SetCurrentTexture,
      "get_current_texture", &Player::GetCurrentTexture,
      "id", &Player::type_id_);

  lua_thread_.detach();
  Logger::Log("Constructed Lua Host", INFO);
}

void LuaHost::Script(string lua_code) {
  {
    std::lock_guard<std::mutex> lg(script_mutex_);
    script_queue_.push(lua_code);
    Logger::Log("Pushed script", INFO);
  }
  cv_.notify_all();
}

std::list<string> LuaHost::GetResults() {
  // Holds the results
  std::list<string> results;
  // Lock the results queue and empty it into the results var
  std::lock_guard<std::mutex> result_lock(result_mutex_);
  while (!result_queue_.empty()) {
    results.push_back(result_queue_.front());
    result_queue_.pop();
  }
  return results;
}

void LuaHost::Execute() {
  Logger::Log("Lua execution thread initiated", INFO);

  while (!kill_lua_thread_) {
    std::unique_lock<std::mutex> lock(script_mutex_);
    cv_.wait_for(lock, 100ms);
    if (script_queue_.empty()) {
      // Logger::Log("False alarm!", INFO);
      continue;
    }

    // Empty out the script queue into our own personal one
    std::queue<string> personal_script_queue;
    while (!script_queue_.empty()) {
      Logger::Log("Queuing " + script_queue_.front(), INFO);
      personal_script_queue.push(script_queue_.front());
      script_queue_.pop();
    }
    // Unlock it so that others can use again
    lock.unlock();

    // Execute queued scripts
    while (!personal_script_queue.empty()) {
      Logger::Log("Executing code `" + personal_script_queue.front() + "`", INFO);

      auto result = lua_state_.safe_script(personal_script_queue.front(),
                                           sol::script_pass_on_error);
      personal_script_queue.pop();

      if (!result.valid()) {
        sol::error err = result;
        std::lock_guard<std::mutex> result_lock(result_mutex_);
        result_queue_.push(err.what());
      } else {
        std::lock_guard<std::mutex> result_lock(result_mutex_);
        result_queue_.push(result);
      }
    }
  }
  thread_done_ = true;
  Logger::Log("Killed lua host", INFO);
}

sol::state& LuaHost::GetState() { return lua_state_; }

LuaHost::~LuaHost() {
  Logger::Log("Killing lua host", INFO);
  kill_lua_thread_ = true;
  cv_.notify_all();

  // Give the thread some time to end on its own, then give up if it can't
  std::this_thread::sleep_for(500ms);
  if (!thread_done_) {
    Logger::Log("Possible failure to gently kill lua host. Forcibly killing...", INFO);
  }
}
