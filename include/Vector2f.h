#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <cmath>

// Class for a mutable vector of two floats, including some useful member functions
// Suspends some minor bits of the Google style guide since it is inheriting from a library
// that does not follow Google style guide
class Vector2f : public sf::Vector2f{
 public:
  // Constructs a Vector2f with no initial values
  Vector2f();

  // Constructs a Vector2f with the given initial values
  Vector2f(float x, float y);

  // Constructs a Vector2f with a given b2Vec2
  Vector2f(b2Vec2 other);

  // Rotate this Vector2f by a given amount
  void Rotate(float theta);

  // Dot this Vector2f with another and return the result
  inline float Dot(Vector2f other) const {
    return this->x * other.x + this->y * other.y;
  }

  // Return the magnitude of this Vector2d
  inline float Magnitude() const {
    return sqrt(this->x * this->x + this->y * this->y);
  }

  // Multiply this Vector2f by a float and return it
  inline Vector2f operator*(float scalar) const {
    return Vector2f(this->x * scalar, this->y * scalar);
  }

  // Divide this Vector2f by a float and return it
  inline Vector2f operator/(float scalar) const {
    return Vector2f(this->x / scalar, this->y / scalar);
  }

  // Add another Vector2f to this Vector2f and return it
  inline Vector2f operator+(const Vector2f& other) const {
    return Vector2f(this->x + other.x, this->y + other.y);
  }

  // Subtract another Vector2f from this Vector2f and return it
  inline Vector2f operator-(const Vector2f& other) const {
    return Vector2f(this->x - other.x, this->y - other.y);
  }

  // Return the normal Vector2f to this Vector2f
  inline Vector2f Norm() const {
    return Vector2f(-this->y, this->x) / Magnitude();
  }

  // Return the distance between this Vector2f and the given
  inline float Distance(Vector2f other) const {
    return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
  }

  // Return the angle between this Vector2f and the given, in radians
  inline float Angle(Vector2f other) const {
    return acos(Dot(other) / (this->Magnitude() * other.Magnitude()));
  }

  inline b2Vec2 AsB2Vec2() {
    return b2Vec2(x, y);
  }

 protected:

 private:
};

#endif // VECTOR2F_H
