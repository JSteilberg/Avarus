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

#include "Entity.h"

Entity::Entity(const sf::Texture &atlas,
               const std::map<string, sf::IntRect> &texture_map, b2World &world)
    : texture_map_(texture_map), atlas_(atlas),
      sprite_(atlas, texture_map.at("norm")) {
  // sprite_.setScale(1,2);
  sprite_.setScale(width_ * consts::kPixelScale / texture_map.at("norm").width,
                   height_ * consts::kPixelScale /
                       texture_map.at("norm").height);

  body_def_.type = b2_dynamicBody;
  body_def_.position.Set(0, 0);

  body_ = world.CreateBody(&body_def_);

  SetCurrentTexture("norm");
}

const sf::Sprite &Entity::GetSprite() {
  sprite_.setPosition(body_->GetPosition().x * consts::kPixelScale,
                      body_->GetPosition().y * consts::kPixelScale);
  sprite_.setRotation(body_->GetAngle());
  return sprite_;
}

void Entity::SetShape(const b2Vec2 *vertices, int vertex_count) {
  shape_.Set(vertices, vertex_count);
  fixture_def_.shape = &shape_;
  fixture_def_.density = 1.0f;
  fixture_def_.friction = 0.3f;
  body_->CreateFixture(&fixture_def_);
}

void Entity::SetCurrentTexture(std::string key) {
  current_texture_ = key;
  sprite_.setTextureRect(texture_map_.at(key));
}

string Entity::GetCurrentTexture() { return current_texture_; }

void Entity::SetPos(b2Vec2 pos) {
  body_->SetTransform(body_->GetPosition() + pos, body_->GetAngle());
}

b2Vec2 Entity::GetPos() { return body_->GetPosition(); }

void Entity::SetVel(b2Vec2 vel) { body_->SetLinearVelocity(vel); }

b2Vec2 Entity::GetVel() { return body_->GetLinearVelocity(); }

void Entity::SetRot(float rot) {
  sprite_.setRotation(rot);
  body_->SetTransform(body_->GetPosition(), rot);
}

float Entity::GetRot() { return body_->GetAngle(); }

void Entity::ApplyForce(b2Vec2 forceVec) {
  body_->ApplyForce(forceVec, body_->GetWorldCenter(), true);
}

Entity::~Entity() {

  // dtor
}
