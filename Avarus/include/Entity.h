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

  // Create an entity with no initial parameters. How useless.
  Entity();

  // Create an entity with an initial main sf::Texture, specified by a string
  Entity(string main_texture);

  // Create an entity with an initial main sf::Texture
  Entity(const sf::Texture& texture);

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

  void Update(const sf::Time& deltaTime);

  virtual ~Entity();

 protected:
  Entity(const sf::VertexArray& vertices);

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
