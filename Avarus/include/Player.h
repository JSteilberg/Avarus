#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Entity.h"

using std::string;

// Class to represent the player
class Player : public Entity {
 public:

  // Create a Player with nothing. How useless.
  Player();

  // Create a Player with an initial sf::Texture
  Player(sf::Texture& texture);

  virtual ~Player();

 protected:

 private:
};

#endif // PLAYER_H
