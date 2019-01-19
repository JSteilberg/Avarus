#include "Vector2f.h"

Vector2f::Vector2f() : sf::Vector2f(0, 0) {}

Vector2f::Vector2f(float x, float y) : sf::Vector2f(x, y) {}

Vector2f::Vector2f(b2Vec2 other) {
  this->x = other.x;
  this->y = other.y;
}

void Vector2f::Rotate(float theta) {
  this->x = (this->x * cos(theta)) - (this->y * sin(theta));
  this->y = (this->x * sin(theta)) + (this->y * cos(theta));
}
