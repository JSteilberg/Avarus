#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/graphics.hpp>
#include <string>

using std::string;

class Entity : public sf::Drawable {
 public:
  Entity();
  virtual ~Entity();

 protected:

 private:
  //  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // ENTITY_H
