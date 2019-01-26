#include "Player.h"

Player::Player(Atlas& atlas) :
  Entity(atlas.GetTexture(), atlas.GetRects(50000), sf::VertexArray(sf::Quads, 4)) {
  sf::Vector2f pos = getPosition();
  vertices_[0].position = sf::Vector2f(pos.x, pos.y);
  vertices_[1].position = sf::Vector2f(pos.x, pos.y + 128);
  vertices_[2].position = sf::Vector2f(pos.x + 64, pos.y + 128);
  vertices_[3].position = sf::Vector2f(pos.x + 64, pos.y);
}

const int Player::GetTypeId() const {
  return type_id_;
}

Player::~Player() {
  //dtor
}
