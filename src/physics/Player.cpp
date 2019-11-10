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

#include "Player.hpp"

Player::Player(Atlas &atlas, b2World &world)
    : Entity(atlas.GetTexture(), atlas.GetRects(50000), world) {
  width_ = 1;
  height_ = 2;

  b2Vec2 pos(0.0, 0.0);
  b2Vec2 vertices[4];
  vertices[0] = b2Vec2(pos.x, pos.y);
  vertices[1] = b2Vec2(pos.x + width_, pos.y);
  vertices[2] = b2Vec2(pos.x + width_, pos.y + height_);
  vertices[3] = b2Vec2(pos.x, pos.y + height_);

  SetShape(vertices, 4);
}

void Player::Update(const sf::Time &delta_time) {
  float t = delta_time.asSeconds();
  // do nothing
}

int Player::GetTypeId() const { return type_id_; }

Player::~Player() {
  // dtor
}
