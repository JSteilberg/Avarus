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

#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "Constants.hpp"
#include "Logger.hpp"

using std::string;

// An Entity is something that interacts physically, can be drawn, and can die
// I hope to be an entity someday
// TODO: Add ability to die
class Entity {
public:
  // Set this Entity's position
  void SetPos(b2Vec2 pos);

  // Get this Entity's position
  b2Vec2 GetPos();

  // Set this Entity's velocity
  void SetVel(b2Vec2 vel);

  // Get this Entity's velocity
  b2Vec2 GetVel();

  // Set this Entity's rotation
  void SetRot(float rot);

  // Get this Entity's rotation
  float GetRot();

  // Apply a force to this Entity
  void ApplyForce(b2Vec2 forceVec);

  // Update this Entity with a given deltaTime
  virtual void Update(const sf::Time &delta_time) = 0;

  // Get the type ID for this Entity
  virtual int GetTypeId() const = 0;

  // Sets the shape of this Entity's body
  void SetShape(const b2Vec2 *vertices, int vertex_count);

  // Gets the sprite used to draw this Entity
  const sf::Sprite &GetSprite();

  // Set the texture rect to display for the sprite
  void SetCurrentTexture(string key);

  // Get the current texture rect key being used to draw the sprite
  string GetCurrentTexture();

  virtual ~Entity();

protected:
  // Basic constructor that includes the atlas texture and corresponding
  // texture rects
  Entity(const sf::Texture &atlas,
         const std::map<string, sf::IntRect> &texture_map, b2World &world);

  // Map of texture subsets to be used by this Entity. The first texture will be
  // mapped to "main".
  const std::map<string, sf::IntRect> &texture_map_;

  // Array of sf::Vector2f that define the shape of this Entity
  // VertexArray vertices_;

  // Reference to the texture to be used
  const sf::Texture &atlas_;

  // Sprite used to draw this Entity
  sf::Sprite sprite_;

  // Name of current texture
  string current_texture_;

  b2BodyDef body_def_;

  b2Body *body_;

  b2PolygonShape shape_;

  b2FixtureDef fixture_def_;

  float width_ = 1;

  float height_ = 2;

private:
};

#endif // ENTITY_H
