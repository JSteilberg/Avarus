#ifndef MAINLOOP_H
#define MAINLOOP_H

//class GameState;
class Game;

#include "GameState.h"
#include "Player.h"

// Class to represent the main loop for the game
class MainLoop : public GameState {
 public:

  // Create an instance of MainLoop without any game to operate on
  MainLoop();

  // Create an instance of MainLoop with a specified game
  MainLoop(Game* game);

  // This is how the main loop do
  virtual void Update();

  virtual ~MainLoop();

 protected:

 private:
  // Main game player
  Player player_;

  // Main game player's texture
  sf::Texture player_texture_;

  // List of Corporeals to update during the update() function
  std::vector<Corporeal> update_list_;
};

#endif // MAINLOOP_H
