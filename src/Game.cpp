#include "Game.h"

Game::Game() :
  // Create window with 800x600 resolution
  window_(sf::VideoMode(800, 600), "Avarus v" + consts::kGameVersion),
  id_registry_("./res/cfg/ids.json"),
  game_atlas_("./res/cfg/atlas.json", id_registry_),
  gravity_(0.0f, 0.0f),
  world_(gravity_),
  player_(game_atlas_, world_),
  main_loop_(player_, world_, dbg_overlay_) {
    //window_.setFramerateLimit(60);
    window_.setKeyRepeatEnabled(false);
    state_stack_.push(&main_loop_);


    dbg_overlay_.Set("ver", string("Avarus v") + consts::kGameVersion);
    dbg_overlay_.Set("thingsps", "0");
    dbg_overlay_.Set("pos", "0");
}

int Game::Start() {

  delta_clock_.restart();
  update_clock_.restart();

  sf::Clock sec_counter_clock;
  sec_counter_clock.restart();

  int frames = 0;
  int updates = 0;

  // Main loop
  while(window_.isOpen()) {
    window_.clear();

    if(update_clock_.getElapsedTime().asSeconds() > 1.0/consts::kUpsPerSec) {
      //world_.Step(update_clock_.getElapsedTime().asSeconds(), 6, 2);
      update_clock_.restart();
      state_stack_.top()->Update(delta_clock_.restart(), window_);
      updates = updates + 1;
    }
    state_stack_.top()->Draw(window_);
    window_.display();

    frames = frames + 1;

    if(sec_counter_clock.getElapsedTime().asSeconds() >= 1) {
      sec_counter_clock.restart();
      dbg_overlay_.Set("thingsps", to_string(frames) + " fps, " + to_string(updates) + " ups");
      frames = 0;
      updates = 0;
    }
  }
  return 0;
}

// Maybe remove this?
void Game::Update(const sf::Event& event) {

}

Game::~Game() {
  // dtor
}
