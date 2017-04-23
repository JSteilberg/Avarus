#include "Corporeal.h"

Corporeal::Corporeal(const sf::Texture& texture,
                     const std::map<string, sf::IntRect>& texture_rects,
                     const sf::VertexArray& vertices) :
  texture_rects_(texture_rects),
  vertices_(vertices),
  texture_(texture) {
  SetMainTextureRect(texture_rects_.at("norm"));
}

void Corporeal::SetMainTextureRect(const sf::IntRect& rectangle) {
  vertices_[0].texCoords = sf::Vector2f(rectangle.left, rectangle.top);  vertices_[1].texCoords = sf::Vector2f(rectangle.left, rectangle.top + rectangle.height);  vertices_[2].texCoords = sf::Vector2f(rectangle.left + rectangle.width, rectangle.top + rectangle.height);  vertices_[3].texCoords = sf::Vector2f(rectangle.left + rectangle.width, rectangle.top);
}

void Corporeal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // getTransform() is defined by sf::Transformable
  states.transform *= getTransform();

  // Apply the current texture
  states.texture = &texture_;

  // TODO override states.shader or states.blendMode if you want

  // Draw the vertex array
  target.draw(vertices_, states);
}

void Corporeal::SetPos(Vector2f pos) {
  setPosition(pos);
}


void Corporeal::AddPos(Vector2f posOffset) {
  move(posOffset);
}

Corporeal::~Corporeal() {
  //dtor
}
