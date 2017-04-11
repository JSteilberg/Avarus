#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameState.cpp"
#include <boost/property_tree/ptree.hpp>
#include "Parser.h"

using boost::property_tree::ptree;
using std::string;

/* IMPORTANT CONSTANTS THAT GET TO BE GLOBAL */
const string kGameVersion = "1.0";
const bool kDebugMode = true;
GameState game_state = MAIN_LOOP;


class Game {
 public:
  Game() : tex_parser("./res/cfg/textures.json") {
    tex_parser.parse();
  }

  void start() {
    std::cout << "ddd" << std::endl;
    std::cout << tex_parser.get_parse_tree().get<string>("player.player_texture") << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Avarus v" + kGameVersion);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
      }
      window.clear();
      window.draw(shape);
      window.display();
    }
  }
 private:
  Parser tex_parser;
//  Player p;
};

int main() {
  Game game;
  game.start();
  return 0;
}


