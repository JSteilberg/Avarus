#ifndef MAINLOOP_H
#define MAINLOOP_H

//class GameState;
class Game;

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "GameState.h"
#include "Player.h"
#include "DebugOverlay.h"
#include "Constants.h"

// Class to represent the main loop for the game
class MainLoop : public GameState {
 public:
  // Create an instance of MainLoop with a specified player
  // Important: Does modify player
  MainLoop(Player& player, b2World& world, DebugOverlay& dbg_overlay);

  // This is how the main loop do
  virtual void Update(const sf::Time& deltaTime, sf::Window& window) override;

  // This is how the drawing do
  virtual void Draw(sf::RenderWindow& window) override;

  virtual ~MainLoop();

protected:

private:

  // Handles the keyboard events
  void HandleKeyEvents(sf::Window& window);

  // Main game player
  Player& player_;

  // Main game player's texture
  sf::Texture player_texture_;

  // List of Entitys to update during the update() function
  std::vector<Entity> update_list_;

  // Holds the Box2D world that
  b2World& world_;

  // Flag to turn on semitransparent debug menu
  bool dbg_menu_on_;

  // Flag to turn the game console on
  bool console_on_;

  DebugOverlay& dbg_overlay_;
};

#endif // MAINLOOP_H
