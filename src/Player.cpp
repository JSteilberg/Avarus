#include "Player.h"

Player::Player(Atlas& atlas, b2World& world) :
  Entity(atlas.GetTexture(), atlas.GetRects(50000), VertexArray(sf::Quads, 4), world) {
  b2Vec2 pos(0.0,0.0);
  vertices_[0].position = sf::Vector2f(pos.x, pos.y);
  vertices_[1].position = sf::Vector2f(pos.x + .75, pos.y);
  vertices_[2].position = sf::Vector2f(pos.x + .75, pos.y + 1.5);
  vertices_[3].position = sf::Vector2f(pos.x, pos.y + 1.5);


  const b2Vec2* verts = vertices_.VerticesAsB2Vec2();
  std::cout << verts[0].x << " | " << verts[0].y << std::endl;  std::cout << verts[1].x << " | " << verts[1].y << std::endl;  std::cout << verts[2].x << " | " << verts[2].y << std::endl;  std::cout << verts[3].x << " | " << verts[3].y << std::endl;

  SetShape(verts, 4);
}

int Player::GetTypeId() const {
  return type_id_;
}

Player::~Player() {
  //dtor
}
