#include "Game.h"

Game::Game() :
  // Create window with 800x600 resolution
  window_(sf::VideoMode(800, 600), "Avarus v" + kGameVersion),
  id_registry_("./res/cfg/ids.json"),
  game_atlas_("./res/cfg/atlas.json", id_registry_),
  gravity_(0.0f, 0.0f),
  world_(gravity_),
  player_(game_atlas_, world_),
  main_loop_(player_, world_) {
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
      world_.Step(1.0/60.0f, 6, 2);
      update_clock_.restart();
      state_stack_.top()->Update(delta_clock_.restart(), event);
    }
    state_stack_.top()->Draw(window_);
    window_.display();
  }
}

// Maybe remove this?
void Game::Update(const sf::Event& event) {

}

Game::~Game() {
  // dtor
}
