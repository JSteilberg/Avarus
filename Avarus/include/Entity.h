#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <map>
#include <SFML/graphics.hpp>
#include <stdexcept>
#include <string>

#include "Vector2f.h"
#include "Corporeal.h"

using std::string;

// An Entity is a Corporeal with the ability to move an accelerate, as well as the possession
// of mass and health
class Entity : public Corporeal {
 public:

  // Set this Entity's velocity
  void SetVel(Vector2f vel);

  // Set this Entity's acceleration
  void SetAcc(Vector2f acc);

  // Add to this Entity's velocity
  void AddVel(Vector2f velOffset);

  // Add to this Entity's acceleration
  void AddAcc(Vector2f accOffset);

  // Apply a force to this Entity, as a vector with units N*m/s^2
  void Force(Vector2f forceVect);

  // Update this Entity with a given deltaTime
  void Update(const sf::Time& deltaTime);

  // Get the type ID for this Corporeal
  virtual const int GetTypeId() const = 0;

  virtual ~Entity();

 protected:
  // Used internally to initialize textures and vertices
  Entity(const sf::Texture& texture,
         const std::map<string, sf::IntRect>& texture_rects,
         const sf::VertexArray& vertices);

  // x and y velocity of this Entity
  Vector2f vel_;

  // x and y acceleration of this Entity
  Vector2f acc_;

  // Mass of this Entity, in Kilograms
  float mass_;

  // Angle of this Entity, in Radians
  float angle_;

 private:

};

#endif // ENTITY_H
