#include "Player.h"

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

int Player::GetTypeId() const { return type_id_; }

Player::~Player() {
  // dtor
}
