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

#ifndef CONSOLELOOP_H
#define CONSOLELOOP_H

#include "Game.hpp"
#include "GameState.hpp"
#include "Logger.hpp"

class DebugOverlay;

class ConsoleLoop : public GameState {
public:
  ConsoleLoop(Game *game);

  // This is how the main loop do
  virtual void Update(const sf::Time &deltaTime, sf::Window &window) override;

  // This is how the drawing do
  virtual void Draw(sf::RenderWindow &window) override;

  virtual const string ToString() const override;

  void HandleKeyEvents(sf::Window &window);

  virtual ~ConsoleLoop();

private:
  Game *game_;
};

#endif // CONSOLELOOP_H
