#include "Player.h"

Player::Player(Atlas& atlas, b2World& world) :
  Entity(atlas.GetTexture(), atlas.GetRects(50000), world) {


  b2Vec2 pos(0.0,0.0);
  b2Vec2 vertices[4];
  vertices[0] = b2Vec2(pos.x, pos.y);
  vertices[1] = b2Vec2(pos.x + .75, pos.y);
  vertices[2] = b2Vec2(pos.x + .75, pos.y + 1.5);
  vertices[3] = b2Vec2(pos.x, pos.y + 1.5);

  SetShape(vertices, 4);
}

int Player::GetTypeId() const {
  return type_id_;
}

Player::~Player() {
  //dtor
}
