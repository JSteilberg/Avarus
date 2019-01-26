#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <SFML/System.hpp>
#include <cmath>

// Class for a mutable vector of two floats, including some useful member functions
// Suspends some minor bits of the Google style guide since it is inheriting from a library
// that does not follow Google style guide
class Vector2f : public sf::Vector2f {
 public:
  // Constructs a Vector2f with no initial values
  Vector2f();

  // Constructs a Vector2f with the given initial values
  Vector2f(float x, float y);

  // Dot this Vector2d with another and return the result
  const float Dot(Vector2f other) const;

  // Return the magnitude of this Vector2d
  const float Magnitude() const;

  // Multiply this Vector2f by a float and return it
  Vector2f operator*(float scalar) const;

  // Add another Vector2f to this Vector2f and return it
  Vector2f operator+(const Vector2f& other) const;

  // Return the distance between this Vector2f and the given
  const float Distance(Vector2f other) const;

  // Return the angle between this Vector2f and the given, in radians
  const float Angle(Vector2f other) const;

  virtual ~Vector2f();
 protected:

 private:
};

#endif // VECTOR2F_H
