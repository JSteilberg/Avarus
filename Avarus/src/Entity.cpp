#include "Entity.h"

Entity::Entity() {
}

Entity::Entity(string main_texture) {
  SetMainTexture(main_texture);
}

Entity::Entity(const sf::Texture& texture) {
  SetMainTexture(texture);
}

Entity::Entity(const sf::VertexArray& vertices) {
  vertices_ = vertices;
}

void Entity::SetMainTexture(string main_texture) {
  sf::Texture texture;
  if (!texture.loadFromFile(main_texture)) {
    throw new std::runtime_error("Error loading texture " + main_texture + "in Entity.");
  }
  this->SetMainTexture(texture);
}

void Entity::SetMainTexture(const sf::Texture& texture) {
  std::cout << "working" << std::endl;
  textures_["main"] = texture;
  current_texture_ = texture;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // getTransform() is defined by sf::Transformable
  states.transform *= getTransform();

  // Apply the current texture
  states.texture = &current_texture_;

  // TODO override states.shader or states.blendMode if you want

  // Draw the vertex array
  target.draw(vertices_, states);
}

Entity::~Entity() {
  // dtor
}
