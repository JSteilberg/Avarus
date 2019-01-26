#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <map>
#include <SFML/graphics.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "Logger.h"
#include "Corporeal.h"
#include "VertexArray.h"

using std::string;

// An Entity is a Corporeal with the ability to die, mainly
// I hope to be an entity someday
// TODO: Add ability to die
class Entity : public Corporeal {
 public:

  // Get the type ID for this Corporeal
  virtual int GetTypeId() const = 0;

  virtual ~Entity();

 protected:
  // Used internally to initialize textures and vertices
  Entity(const sf::Texture& texture,
         const std::map<string, sf::IntRect>& texture_rects,
         const VertexArray& vertices,
         b2World& world);

 private:

};

#endif // ENTITY_H
