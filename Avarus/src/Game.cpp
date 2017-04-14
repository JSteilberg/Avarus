#include "Game.h"

Game::Game() : tex_parser_("./res/cfg/textures.json"), window_(sf::VideoMode(800, 600), "Avarus v" + kGameVersion) {

  window_.setFramerateLimit(60);
  tex_parser_.Parse();
  tex_parse_tree_ = tex_parser_.GetParseTree();

  state_stack_.push(MainLoop(this));

  if(!player_texture_.loadFromFile(tex_parse_tree_.get<string>("player.player_texture"))) {
    throw new std::runtime_error("Failed to load Player texture from " + tex_parse_tree_.get<string>("player.player_texture"));
  }
  player_.SetTexture(player_texture_);
}

void Game::Start() {
  while (window_.isOpen()) {
    window_.clear();
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }
    }

    Update(event);
    window_.draw(player_);
    window_.display();
  }
}


void Game::Update(const sf::Event& event) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    player_.AddPos(Vector2f(0, -.5));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    player_.AddPos(Vector2f(0,  .5));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player_.AddPos(Vector2f(-.5, 0));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player_.AddPos(Vector2f( .5, 0));
  }
}

Game::~Game() {
  // dtor
}
