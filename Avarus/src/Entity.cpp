#include "Entity.h"

Entity::Entity() {

}

Entity::Entity(const sf::Texture& texture) : Corporeal(texture) {}

Entity::Entity(const sf::VertexArray& vertices) : Corporeal(vertices) {}

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
