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
GNU Lesser General Public License for more details.

A copy of the GNU Affero General Public License should accompany
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef GAME_H
#define GAME_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Atlas.hpp"
#include "ConfigLoader.hpp"
#include "Console.hpp"
#include "ConsoleLoop.hpp"
#include "Constants.hpp"
#include "GameState.hpp"
#include "MainLoop.hpp"
#include "ObjRegister.hpp"
#include "Parser.hpp"
#include "Player.hpp"

using std::list;
using std::shared_ptr;

class MainLoop;
class ConsoleLoop;

// Class to run an instance of the game.
// All you have to do is declare an instance and run .start()
class Game {
public:
  Game();

  int Start();

  void Update();

  void AddState(shared_ptr<GameState> new_state);

  void RemoveState(shared_ptr<GameState> remove_state);

  // Used to get the amount of time to draw a frame
  sf::Clock delta_clock_;

  // Used to ensure updating happens a max of 60 times per second
  sf::Clock update_clock_;

  // Holds the current state of the game (Used for menus, main loop, etc.)
  list<shared_ptr<GameState>> state_list_;

  // Holds the new states that will be added after current update
  list<shared_ptr<GameState>> new_states_;

  // Holds the states that will be removed after current update
  list<shared_ptr<GameState>> remove_states_;

  virtual ~Game();

  // private:
  // Holds config data for the game
  ConfigLoader game_config_;

  int window_width_;

  int window_height_;

  // Parsers for the game's map (will be removed at some point)
  Parser map_parser_;

  // Main window for the game
  sf::RenderWindow window_;

  // Used for converting sprite int IDs into corresponding names
  IdRegister id_registry_;

  // Property trees that correspond to the above parsers
  // ptree tex_parse_tree_, map_parse_tree_;

  // Holds main texture and texture coordinates for all Sprites in the game
  Atlas game_atlas_;

  // Necessary for creating a Box2D world. Unfortunately, since this is space,
  // Our gravity is a bit more complicated than that and must be handled
  // separately Therefore the world is given a 0 vector for gravity
  const b2Vec2 gravity_;

  // The Box2D world
  b2World world_;

  // Main player for the game
  Player player_;

  // Main loop for the game
  shared_ptr<MainLoop> main_loop_;

  // Loop for displaying console
  shared_ptr<ConsoleLoop> console_loop_;

  DebugOverlay dbg_overlay_;

  Console console_overlay_;

  sf::Clock thingsps_counter_clock_;
};

#endif // GAME_H
