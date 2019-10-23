#include "Entity.h"

Entity::Entity(const sf::Texture& texture,
               const std::map<string, sf::IntRect>& texture_rects,
               b2World& world) :
  Corporeal(texture, texture_rects, world) {}



Entity::~Entity() {
  // dtor
}
