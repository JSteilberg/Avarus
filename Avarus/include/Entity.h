#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <SFML/graphics.hpp>
#include <stdexcept>
#include <string>

#include "Vector2f.h"

using std::string;

class Entity : public sf::Drawable, public sf::Transformable {
 public:
  // Create an entity with no initial parameters. How useless.
  Entity();


  // Create an entity with an initial main sf::Texture, specified by a string
  Entity(string main_texture);

  // Create an entity with an initial main sf::Texture
  Entity(const sf::Texture& texture);

  // Draw member function inherited from sf::Drawable, called when this Entity is drawn
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  // Sets the main texture based on a file path
  void SetMainTexture(string main_texture);

  // Sets the main texture based on a sf::Texture
  void SetMainTexture(const sf::Texture& texture);

  virtual ~Entity();

 protected:
  Entity(const sf::VertexArray& vertices);

  // Array of sf::Vector2f that define the shape of this Entity
  sf::VertexArray vertices_;

  // Map of textures to be used by the entity. The first texture will be mapped to "main".
  std::map<string, sf::Texture> textures_;

  // Current texture to use
  sf::Texture current_texture_;

  // x and y coordinates of this Entity
  Vector2f pos_;

  // x and y velocity of this Entity
  Vector2f vel_;

  // x and y acceleration of this Entity
  Vector2f acc_;

 private:

};

#endif // ENTITY_H
