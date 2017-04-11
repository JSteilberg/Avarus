#include "Vector2d.h"

Vector2d::Vector2d()
{
    this->x = 0;
    this->y = 0;
}

Vector2d::Vector2d(double x, double y) {
    this->x = x;
    this->y = y;
}

const double Vector2d::distance(Vector2d other) {
    return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
}

const double Vector2d::dot(Vector2d other) {
    return this->x * other.x + this->y * other.y;
}

const double Vector2d::angle(Vector2d other) {
    return acos(this->dot(other) / (this->magnitude() * other.magnitude()));
}

const double Vector2d::magnitude() const {
    return sqrt(this->x * this-> x + this->y * this->y);
}

Vector2d::~Vector2d()
{
    //dtor
}
