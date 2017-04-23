#include "Corporeal.h"

Corporeal::Corporeal(const sf::Texture& texture,
                     const std::map<string, sf::IntRect>& texture_rects,
                     const sf::VertexArray& vertices) :
  texture_rects_(texture_rects),
  vertices_(vertices) {
  SetTexture(texture);
  SetMainTextureRect(sf::IntRect(208, 0, 64, 32));//texture_rects_.at("norm"));
}

void Corporeal::SetTexture(const sf::Texture& texture) {
  setTexture(texture);
}

void Corporeal::SetMainTextureRect(const sf::IntRect& rectangle) {
  setTextureRect(rectangle);
}

void Corporeal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // getTransform() is defined by sf::Transformable
  states.transform *= getTransform();

  // Apply the current texture
  states.texture = getTexture();

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
