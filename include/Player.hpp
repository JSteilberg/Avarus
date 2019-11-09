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

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Atlas.hpp"
#include "Entity.hpp"

using std::string;

// Class to represent the player
class Player : public Entity {
 public:
  // Create a Player with an initial Atlas
  Player(Atlas &atlas, b2World &world);

  virtual ~Player();

  virtual void Update(const sf::Time &delta_time) override;

  virtual int GetTypeId() const override;

 private:
  // Corresponds to the player "type"
  const int type_id_ = 50000;
};

#endif  // PLAYER_H
