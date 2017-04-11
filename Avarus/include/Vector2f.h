#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <SFML/System.hpp>
#include <cmath>

// Class for a mutable vector of two floats, including some useful member functions
class Vector2f : public sf::Vector2f {
 public:
  Vector2f();
  Vector2f(float x, float y);
  virtual ~Vector2f();
  // Dot this Vector2d with another and return the result
  const float dot(Vector2f other);
  // Return the magnitude of this Vector2d
  const float magnitude() const;
  // Multiply this Vector2f by a float and return it
  Vector2f operator*(const float scalar);
  // Return the distance between this Vector2f and the given
  const float distance(Vector2f other);
  // Return the angle between this Vector2f and the given, in radians
  const float angle(Vector2f other);
 protected:

 private:
};

#endif // VECTOR2F_H
