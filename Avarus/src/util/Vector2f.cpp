#include "Vector2f.h"

Vector2f::Vector2f() {
  this->x = 0;
  this->y = 0;
}

Vector2f::Vector2f(float x, float y) {
  this->x = x;
  this->y = y;
}

const float Vector2f::distance(Vector2f other) {
  return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
}

const float Vector2f::dot(Vector2f other) {
  return this->x * other.x + this->y * other.y;
}

const float Vector2f::angle(Vector2f other) {
  return acos(this->dot(other) / (this->magnitude() * other.magnitude()));
}

const float Vector2f::magnitude() const {
  return sqrt(this->x * this-> x + this->y * this->y);
}

Vector2f::~Vector2f() {
  //dtor
}
