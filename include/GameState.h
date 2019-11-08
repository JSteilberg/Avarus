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

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <string>

using std::string;

class Game;

// Usually going on an std::stack of GameStates, an instance of GameState
// represents a specific mode the Game is currently in.
class GameState {
public:
  // Creates a GameState with no attributes
  GameState();

  // This method should be called during every update in the main Game loop
  virtual void Update(const sf::Time &deltaTime, sf::Window &window) = 0;

  virtual void Draw(sf::RenderWindow &window) = 0;

  virtual const string ToString() const = 0;

  virtual ~GameState();

protected:
  // Holds the game that cerated the GameState
  Game *game_;

private:
};

#endif // GAMESTATE_H
