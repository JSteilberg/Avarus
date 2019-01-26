#ifndef MAINLOOP_H
#define MAINLOOP_H

//class GameState;
class Game;

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "GameState.h"
#include "Player.h"

// Class to represent the main loop for the game
class MainLoop : public GameState {
 public:

  // Create an instance of MainLoop with a specified player
  // Important: Does modify player
  MainLoop(Player& player, b2World& world);

  // This is how the main loop do
  virtual void Update(const sf::Time& deltaTime, const sf::Event& event) override;

  // This is how the drawing do
  virtual void Draw(sf::RenderWindow& window);

  virtual ~MainLoop();

 protected:

 private:
  // Main game player
  Player& player_;

  // Main game player's texture
  sf::Texture player_texture_;

  // List of Corporeals to update during the update() function
  std::vector<Corporeal> update_list_;

  b2World& world_;
};

#endif // MAINLOOP_H
