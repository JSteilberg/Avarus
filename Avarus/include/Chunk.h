#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include "Block.h"

class Chunk {
 public:
  Chunk();
  virtual ~Chunk();

 protected:

 private:
  std::vector<Block> blocks();
};

#endif // CHUNK_H
