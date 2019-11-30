#ifndef LUAHOST_H
#define LUAHOST_H

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <list>
#include <lua.hpp>
#include <queue>
#include <sol/sol.hpp>
#include <string>
#include <thread>
#include <utility>

#include "Player.hpp"

using std::string;
using namespace std::chrono_literals;

class LuaHost {
 public:
  LuaHost();

  void Script(string lua_code);

  sol::state& GetState();

  ~LuaHost();

  void printError(const string& variableName, const string& reason);


  // Returns a list of results from queued scripts
  std::list<string> GetResults();

 private:

  // Runs a loop, waiting for scripts to enter the queue
  void Execute();

  // Holds the lua interpreter state
  sol::state lua_state_;

  // Queue containing scripts to be executed by the thread
  std::queue<string> script_queue_;

  // Queue containing results or errors from executed scripts
  std::queue<string> result_queue_;

  std::condition_variable cv_;

  // Mutex used for exclusive access to script_queue_
  std::mutex script_mutex_;

  // Mutex used for exclusive access to result_queue_
  std::mutex result_mutex_;

  // Flag to kill the lua thread willingly
  bool kill_lua_thread_;

  // Constantly pops from script_queue_, executing all items then placing the
  // results in result_queue
  std::thread lua_thread_;
};

#endif  // LUAHOST_H
