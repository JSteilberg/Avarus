#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Entity.h"

using std::string;

class Player : public Entity {
 public:
  Player();
  virtual ~Player();
  Player(string main_texture);
  Player(sf::Texture& texture);

 protected:

 private:
};

#endif // PLAYER_H
