#include "VertexArray.h"
#include <iostream>
#include "Logger.h"
VertexArray::VertexArray() : sf::VertexArray() {}

VertexArray::VertexArray(sf::PrimitiveType type, size_t vertex_count) :
  sf::VertexArray(type, vertex_count) {}

const b2Vec2* VertexArray::VerticesAsB2Vec2() const {
  std::vector<b2Vec2> ans(getVertexCount());
  for(unsigned i = 0; i < getVertexCount(); ++i) {
      std::cout << i << " | x: " << (*this)[i].position.x
        << "  y: " << (*this)[i].position.y  << std::endl;

    ans[i] = b2Vec2((*this)[i].position.x, (*this)[i].position.y);
  }
  return ans.data();
}

VertexArray::~VertexArray() {
  //dtor
}
