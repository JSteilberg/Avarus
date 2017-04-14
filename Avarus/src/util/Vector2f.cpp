#include "Vector2f.h"

Vector2f::Vector2f() {
  this->x = 0;
  this->y = 0;
}

Vector2f::Vector2f(float x, float y) {
  this->x = x;
  this->y = y;
}

const float Vector2f::Distance(Vector2f other) const {
  return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
}

const float Vector2f::Dot(Vector2f other) const {
  return this->x * other.x + this->y * other.y;
}

const float Vector2f::Angle(Vector2f other) const {
  return acos(Dot(other) / (this->Magnitude() * other.Magnitude()));
}

const float Vector2f::Magnitude() const {
  return sqrt(this->x * this->x + this->y * this->y);
}

Vector2f Vector2f::operator*(float scalar) const {
  return Vector2f(this->x * scalar, this->y * scalar);
}

Vector2f Vector2f::operator+(const Vector2f& other) const {
  return Vector2f(this->x + other.x, this->y + other.y);
}


Vector2f::~Vector2f() {
  //dtor
}
