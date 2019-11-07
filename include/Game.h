#ifndef GAME_H
#define GAME_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include "Atlas.h"
#include "ConfigLoader.h"
#include "Constants.h"
#include "GameState.h"
#include "MainLoop.h"
#include "ObjRegister.h"
#include "Parser.h"
#include "Player.h"
#include "Console.h"

// Class to run an instance of the game.
// All you have to do is declare an instance and run .start()
class Game {
public:
  Game();

  int Start();

  void Update(const sf::Event &event);

  // Used to get the amount of time to draw a frame
  sf::Clock delta_clock_;

  // Used to ensure updating happens a max of 60 times per second
  sf::Clock update_clock_;

  // Holds the current state of the game (Used for menus, main loop, etc.)
  std::stack<std::shared_ptr<GameState>> state_stack_;

  virtual ~Game();

private:
  // Holds config data for the game
  ConfigLoader game_config_;

  // Parsers for the game's map (will be removed at some point)
  Parser map_parser_;

  // Main window for the game
  sf::RenderWindow window_;

  // Used for converting sprite int IDs into corresponding names
  IdRegister id_registry_;

  // Property trees that correspond to the above parsers
  // ptree tex_parse_tree_, map_parse_tree_;

  // Holds main texture and texture coordinates for all Sprites in the game
  Atlas game_atlas_;

  // Necessary for creating a Box2D world. Unfortunately, since this is space,
  // Our gravity is a bit more complicated than that and must be handled
  // separately Therefore the world is given a 0 vector for gravity
  const b2Vec2 gravity_;

  // The Box2D world
  b2World world_;

  // Main player for the game
  Player player_;

  // Main loop for the game
  std::shared_ptr<MainLoop> main_loop_;

  DebugOverlay dbg_overlay_;

  Console console_overlay_;
};

#endif // GAME_H
