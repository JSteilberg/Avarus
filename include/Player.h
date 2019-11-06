#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Atlas.h"
#include "Entity.h"

using std::string;

// Class to represent the player
class Player : public Entity {
public:
  // Create a Player with an initial Atlas
  Player(Atlas &atlas, b2World &world);

  virtual ~Player();

  virtual int GetTypeId() const override;

protected:
private:
  // Corresponds to the player "type"
  const int type_id_ = 50000;
};

#endif // PLAYER_H
