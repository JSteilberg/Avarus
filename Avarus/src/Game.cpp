#include "Game.h"

Game::Game() : tex_parser_("./res/cfg/atlas.json"), window_(sf::VideoMode(800, 600), "Avarus v" + kGameVersion) {

  window_.setFramerateLimit(5);
  tex_parser_.Parse();
  tex_parse_tree_ = tex_parser_.GetParseTree();

  player_.SetTexture(player_texture_);
  main_loop_ = MainLoop(player_);
  state_stack_.push(&main_loop_);

  if(!player_texture_.loadFromFile(tex_parse_tree_.get<string>("player.player_texture"))) {
    throw new std::runtime_error("Failed to load Player texture from " + tex_parse_tree_.get<string>("player.player_texture"));
  }
}

void Game::Start() {
  delta_clock_.restart();
  update_clock_.restart();
  // Main loop
  while (window_.isOpen()) {
    window_.clear();

    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      } else if (event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Escape) {
          window_.close();
        }
      }
    }
    std::cout << "CUNT " << std::endl;
    if(update_clock_.getElapsedTime().asSeconds() > 1.0/60.0) {
      update_clock_.restart();
      state_stack_.top()->Update(delta_clock_.restart(), event);
    }
    state_stack_.top()->Draw(window_);
    window_.display();
  }
}


void Game::Update(const sf::Event& event) {

}

Game::~Game() {
  // dtor
}
