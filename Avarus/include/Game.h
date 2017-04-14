#ifndef GAME_H
#define GAME_H

#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include <stdexcept>
#include <vector>

#include "Corporeal.h"
#include "Gamestate.h"
#include "MainLoop.h"
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

  // Debug mode
  const bool kDebugMode = true;

  // Used to get the amount of time to draw a frame
  sf::Clock deltaClock;

  // Holds the current state of the game (Used for menus, main loop, etc.)
  std::stack<GameState> state_stack_;

  virtual ~Game();

 private:

  // Parsers for the game's textures and map (map will be changed at some point)
  Parser tex_parser_, map_parser_;

  // Property trees that correspond to the above parsers
  ptree tex_parse_tree_, map_parse_tree_;


  Player player_;

  sf::Texture player_texture_;

  sf::RenderWindow window_;
  //sf::Texture atlas_;
};

#endif // GAME_H
