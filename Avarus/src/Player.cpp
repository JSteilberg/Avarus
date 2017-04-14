#include "Player.h"

Player::Player() : Entity(sf::VertexArray(sf::Quads, 4)) {

  sf::Vector2f pos = getPosition();
  vertices_[0].position = sf::Vector2f(pos.x, pos.y);
  vertices_[1].position = sf::Vector2f(pos.x, pos.y + 128);
  vertices_[2].position = sf::Vector2f(pos.x + 64, pos.y + 128);
  vertices_[3].position = sf::Vector2f(pos.x + 64, pos.y);

  vertices_[0].texCoords = sf::Vector2f(0, 0);
  vertices_[1].texCoords = sf::Vector2f(0, 128);
  vertices_[2].texCoords = sf::Vector2f(64, 128);
  vertices_[3].texCoords = sf::Vector2f(64, 0);
}

Player::Player(sf::Texture& texture) : Entity(texture) {

}

Player::~Player() {
  //dtor
}
