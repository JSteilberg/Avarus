#include "Game.h"

Game::Game() :
  window_(sf::VideoMode(800, 600), "Avarus v" + kGameVersion),
  id_registry_("./res/cfg/ids.json"),
  game_atlas_("./res/cfg/atlas.json", id_registry_),
  player_(game_atlas_),
  main_loop_(player_) {

  //window_.setFramerateLimit(60);
  state_stack_.push(&main_loop_);
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
