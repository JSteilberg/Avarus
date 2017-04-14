#include "Corporeal.h"

Corporeal::Corporeal() {
  //ctor
}

Corporeal::Corporeal(const sf::Texture& texture) {
  SetTexture(texture);
}

Corporeal::Corporeal(const sf::Texture& texture, const sf::IntRect& rectangle) {
  SetTexture(texture);
  SetMainTextureRect(rectangle);
}

Corporeal::Corporeal(const sf::VertexArray& vertices) {
  vertices_ = vertices;
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
