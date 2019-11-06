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
  // ArrayList of Blocks in the chunk
  std::vector<Block> blocks_;
};

#endif // CHUNK_H
