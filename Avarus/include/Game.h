#ifndef GAME_H
#define GAME_H

#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include <stdexcept>
#include <vector>

#include "Atlas.h"
#include "Corporeal.h"
#include "Gamestate.h"
#include "MainLoop.h"
#include "ObjRegister.h"
#include "Parser.h"
#include "Player.h"

using boost::property_tree::ptree;

// Class to run an instance of the game.
// All you have to do is declare an instance and run .start()
class Game {
 public:
  Game();

  void Start();

  void Update(const sf::Event& event);

  // Current version of the game... self explanatory
  const string kGameVersion = "1.0";

  // Used to get the amount of time to draw a frame
  sf::Clock delta_clock_;

  // Used to ensure updating happens a max of 60 times per second
  sf::Clock update_clock_;

  // Holds the current state of the game (Used for menus, main loop, etc.)
  std::stack<GameState*> state_stack_;

  virtual ~Game();

 private:

  // Parsers for the game's map (will be removed at some point)
  Parser map_parser_;

  // Main window for the game
  sf::RenderWindow window_;

  // Used for converting sprite int IDs into corresponding names
  IdRegister id_registry_;

  // Property trees that correspond to the above parsers
  ptree tex_parse_tree_, map_parse_tree_;

  // Holds main texture and texture coordinates for all Sprites in the game
  Atlas game_atlas_;

  // Main player for the game
  Player player_;

  // Main loop for the game
  MainLoop main_loop_;

};

#endif // GAME_H
