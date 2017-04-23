#include "Entity.h"

Entity::Entity(const sf::Texture& texture,
               const std::map<string, sf::IntRect>& texture_rects,
               const sf::VertexArray& vertices) :
  Corporeal(texture, texture_rects, vertices) {}

void Entity::Update(const sf::Time& deltaTime) {
  vel_ = vel_ + acc_;
  AddPos(vel_ * deltaTime.asSeconds());
  acc_ = Vector2f(0, 0);
}

void Entity::SetVel(Vector2f vel) {
  vel_ = vel;
}

void Entity::SetAcc(Vector2f acc) {
  acc_ = acc;
}

void Entity::AddVel(Vector2f velOffset) {
  vel_ = vel_ + velOffset;
}

void Entity::AddAcc(Vector2f accOffset) {
  acc_ = acc_ + accOffset;
}

Entity::~Entity() {
  // dtor
}
