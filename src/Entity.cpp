#include "Entity.h"

Entity::Entity(const sf::Texture& texture,
               const std::map<string, sf::IntRect>& texture_rects,
               const VertexArray& vertices,
               b2World& world) :
  Corporeal(texture, texture_rects, vertices, world) {}



Entity::~Entity() {
  // dtor
}
