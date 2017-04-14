#ifndef CORPOREAL_H
#define CORPOREAL_H

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

#include "Vector2f.h"

using std::string;

// A Corporeal is a sprite with the ability to collide and return opposite forces
class Corporeal : public sf::Sprite {
 public:

  // Creates a Coporeal with no attributes. Pretty useless.
  Corporeal();

  // Create a Corporeal with an initial main sf::Texture
  Corporeal(const sf::Texture& texture);

  // Create a Corporeal with an initial main sf::Texture and texture coordinates
  Corporeal(const sf::Texture& texture, const sf::IntRect& rectangle);

  // Sets the main texture based on a sf::Texture, wrapper for sf::Sprite::setTexture
  void SetTexture(const sf::Texture& texture);

  // Set the main bounding rectangle for this Corporeal's sf::Texture
  void SetMainTextureRect(const sf::IntRect& rectangle);

  // Draw member function inherited from sf::Drawable, called when this Corporeal is drawn
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  // Set this Corporeal's position to a given Vector2f
  void SetPos(Vector2f pos);

  // Offset this Corporeal's position by a given Vector2f
  void AddPos(Vector2f posOffset);

  virtual ~Corporeal();

 protected:

  // Constructs this Corporeal without any texture, only vertices
  Corporeal(const sf::VertexArray& vertices);

  // Array of sf::Vector2f that define the shape of this Corporeal
  sf::VertexArray vertices_;

  // Map of texture subsets to be used by this Corporeal. The first texture will be mapped to "main".
  std::map<string, sf::IntRect&> textures_;

 private:
};

#endif // CORPOREAL_H
