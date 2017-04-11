#include "Player.h"

Player::Player() : Entity(sf::VertexArray(sf::Quads, 4)) {

  vertices_[0].position = sf::Vector2f(pos_.x, pos_.y);
  vertices_[1].position = sf::Vector2f(pos_.x, pos_.y + 128);
  vertices_[2].position = sf::Vector2f(pos_.x + 64, pos_.y + 128);
  vertices_[3].position = sf::Vector2f(pos_.x + 64, pos_.y);

  vertices_[0].texCoords = sf::Vector2f(0, 0);
  vertices_[1].texCoords = sf::Vector2f(0, 128);
  vertices_[2].texCoords = sf::Vector2f(64, 128);
  vertices_[3].texCoords = sf::Vector2f(64, 0);
}

Player::Player(string main_texture) : Entity(main_texture) {

}

Player::Player(sf::Texture& texture) : Entity(texture) {

}

Player::~Player() {
  //dtor
}
