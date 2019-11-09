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

#ifndef MAINLOOP_H
#define MAINLOOP_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <string>

#include "Console.hpp"
#include "Constants.hpp"
#include "DebugOverlay.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "Player.hpp"

using std::string;

// Class to represent the main loop for the game
class MainLoop : public GameState {
 public:
  // Create an instance of MainLoop with a specified player
  // Important: Does modify player
  // MainLoop(Player &player, b2World &world, DebugOverlay &dbg_overlay,
  //         Console &console_overlay);
  MainLoop(Game *game);

  // This is how the main loop do
  virtual void Update(const sf::Time &deltaTime, sf::Window &window) override;

  // This is how the drawing do
  virtual void Draw(sf::RenderWindow &window) override;

  virtual const string ToString() const override;

  MainLoop(const MainLoop &other);

  MainLoop operator=(const MainLoop &other);

  virtual ~MainLoop();

 private:
  // Handles the keyboard events
  void HandleKeyEvents(sf::Window &window);

  Game *game_;
  // Main game player
  // Player &player_;

  // Main game player's texture
  // sf::Texture player_texture_;

  // List of Entity's to update during the update() function
  std::vector<Entity> update_list_;

  // Holds the Box2D world that
  // b2World &world_;

  // Flag to turn the game console on
  bool console_on_;

  // DebugOverlay &dbg_overlay_;

  // Console &console_overlay_;
};

#endif  // MAINLOOP_H
