#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class VertexArray : public sf::VertexArray {
  public:

    VertexArray();

    explicit VertexArray(sf::PrimitiveType type, size_t vertex_count);

    const b2Vec2* VerticesAsB2Vec2() const;

    virtual ~VertexArray();

  protected:

  private:
};

#endif // VERTEXARRAY_H
