#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameState.cpp"
#include "Parser.h"
#include "Player.h"

using boost::property_tree::ptree;
using std::string;

/* IMPORTANT CONSTANTS/VARIABLES THAT GET TO BE GLOBAL */
const string kGameVersion = "1.0";
const bool kDebugMode = true;
GameState game_state = MAIN_LOOP;


class Game {
 public:
  Game() : tex_parser_("./res/cfg/textures.json") {
    tex_parser_.Parse();
    tex_parse_tree_ = tex_parser_.GetParseTree();
    player_.SetMainTexture(tex_parse_tree_.get<string>("player.player_texture"));
  }

  void start() {
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
      window.draw(player_);
      //window.draw(shape);
      window.display();
    }
  }
 private:
  Parser tex_parser_, map_parser_;
  ptree tex_parse_tree_, map_parse_tree_;
  Player player_;
};

int main() {
  Game game;
  game.start();
  return 0;
}


