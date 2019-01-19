#ifndef VERTEX_H
#define VERTEX_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Vector2f.h"

class Vertex : public sf::Vertex {
  public:
    Vertex();

    virtual ~Vertex();

    Vector2f& position;

  protected:

  private:
};

#endif // VERTEX_H
