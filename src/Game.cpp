/*             ___
              / | |_   _ ___ _ __ __  __ _____
             / /| | | / /   |  __/ / / /_____/
            / / | | |/ / /| | | / /_/ /__\ \
           /_/  |_|___/_/ |_|_| \____/_____/

Copyright (C) 2019 Jack Steilberg <jsteil123@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Affero General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

A copy of the GNU Affero General Public License should accompany
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "Game.hpp"

Game::Game()
    : game_config_(consts::kConfigLocation),
      window_width_(game_config_.GetIntVar("window_width")),
      window_height_(game_config_.GetIntVar("window_height")),
      window_(sf::VideoMode(window_width_, window_height_),
              "Avarus v" + consts::kGameVersion),
      id_registry_(game_config_.GetVar("id_registry")),
      game_atlas_(game_config_.GetVar("game_atlas"), id_registry_),
      gravity_(0.0f, 0.0f),
      world_(gravity_),
      player_(game_atlas_, world_),
      main_loop_(std::make_shared<MainLoop>(this)),
      console_loop_(std::make_shared<ConsoleLoop>(this)),
      dbg_overlay_(),
      console_overlay_(5, window_height_, 30, 20, 20),
      state_list_(),
      new_states_(),
      remove_states_(),
      delta_clock_(),
      update_clock_() {
  // window_.setFramerateLimit(60);
  window_.setKeyRepeatEnabled(false);
  state_list_.push_front(main_loop_);

  dbg_overlay_.Set("ver", string("Avarus v") + consts::kGameVersion);
  dbg_overlay_.Set("thingsps", "0");
  dbg_overlay_.Set("pos", "player pos: 0,0");
}

int Game::Start() {
  delta_clock_.restart();
  update_clock_.restart();

  sf::Clock thingsps_counter_clock;
  thingsps_counter_clock.restart();
  int frames = 0;
  int updates = 0;

  // Main loop
  while (window_.isOpen()) {
    if (update_clock_.getElapsedTime().asSeconds() >=
        1.0 / consts::kUpsPerSec) {
      Update();
      updates = updates + 1;
    }

    if (thingsps_counter_clock.getElapsedTime().asSeconds() >= 1) {
      thingsps_counter_clock.restart();
      dbg_overlay_.Set("thingsps", to_string(frames) + " fps, " +
                                       to_string(updates) + " ups");
      frames = 0;
      updates = 0;
    }

    window_.clear();
    for (auto &state : state_list_) {
      state->Draw(window_);
    }
    window_.display();
    frames = frames + 1;
  }

  /*while (!state_stack_.empty()) {
      GameState* gs = state_stack_.top();
      Logger::Log("Delete state: " + gs->ToString(), INFO);
      delete gs;
      state_stack_.pop();
      }*/

  return 0;
}

void Game::Update() {
  update_clock_.restart();
  state_list_.back()->Update(delta_clock_.restart(), window_);

  for (auto &new_state : new_states_) {
    Logger::Log("Added new state " + new_state->ToString(), INFO);
    state_list_.push_back(new_state);
  }
  new_states_.clear();

  for (auto &remove_state : remove_states_) {
    Logger::Log("Removed state " + remove_state->ToString(), INFO);
    state_list_.remove(remove_state);
  }
  remove_states_.clear();
}

void Game::AddState(shared_ptr<GameState> new_state) {
  new_states_.push_back(new_state);
}

void Game::RemoveState(shared_ptr<GameState> remove_state) {
  /*for (auto &state : state_list_) {
  if (state.ToString() == state_name) {

  }
  }*/
  remove_states_.push_front(remove_state);
}

Game::~Game() {
  // dtor
}
