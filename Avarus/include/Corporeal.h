#ifndef CORPOREAL_H
#define CORPOREAL_H

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

#include "Atlas.h"
#include "Vector2f.h"

using std::string;

// A Corporeal is a Drawable with the ability to collide and return opposite forces
class Corporeal : public sf::Drawable, public sf::Transformable {
 public:

  // Set the main bounding rectangle for this Corporeal's sf::Texture
  void SetMainTextureRect(const sf::IntRect& rectangle);

  // Draw member function inherited from sf::Drawable, called when this Corporeal is drawn
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  // Set this Corporeal's position to a given Vector2f
  void SetPos(Vector2f pos);

  // Offset this Corporeal's position by a given Vector2f
  void AddPos(Vector2f posOffset);

  // Get the type ID for this Corporeal
  virtual const int GetTypeId() const = 0;

  virtual ~Corporeal();

 protected:

  // Constructs this Corporeal without any texture, only vertices
  Corporeal(const sf::Texture& texture,
            const std::map<string, sf::IntRect>& texture_rects,
            const sf::VertexArray& vertices);

  // Map of texture subsets to be used by this Corporeal. The first texture will be mapped to "main".
  const std::map<string, sf::IntRect>& texture_rects_;

  // Array of sf::Vector2f that define the shape of this Corporeal
  sf::VertexArray vertices_;

  const sf::Texture& texture_;

 private:
};

#endif // CORPOREAL_H
