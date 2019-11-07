#include "Game.h"

Game::Game()
    : game_config_("./res/cfg/config.json"),
      window_width_(game_config_.GetIntVar("window_width")),
      window_height_(game_config_.GetIntVar("window_height")),
      window_(sf::VideoMode(window_width_, window_height_),
              "Avarus v" + consts::kGameVersion),
      id_registry_("./res/cfg/ids.json"),
      game_atlas_("./res/cfg/atlas.json", id_registry_), gravity_(0.0f, 0.0f),
      world_(gravity_), player_(game_atlas_, world_), dbg_overlay_(),
      console_overlay_(window_width_, window_height_, 500, 300) {

  main_loop_ = std::make_shared<MainLoop>(shared_ptr<Game>(this));
  //        player_, world_, dbg_overlay_, console_overlay_);

  // window_.setFramerateLimit(60);
  window_.setKeyRepeatEnabled(false);
  state_list_.push_front(main_loop_);

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
  while (window_.isOpen()) {
    window_.clear();
    if (update_clock_.getElapsedTime().asSeconds() >=
        1.0 / consts::kUpsPerSec) {
      // world_.Step(update_clock_.getElapsedTime().asSeconds(), 6, 2);
      update_clock_.restart();
      state_list_.front()->Update(delta_clock_.restart(), window_);
      updates = updates + 1;
    }

    for (auto &state : state_list_) {
      state->Draw(window_);
    }
    window_.display();

    frames = frames + 1;

    if (sec_counter_clock.getElapsedTime().asSeconds() >= 1) {
      sec_counter_clock.restart();
      dbg_overlay_.Set("thingsps", to_string(frames) + " fps, " +
                                       to_string(updates) + " ups");
      frames = 0;
      updates = 0;
    }
  }

  for (auto &new_state : new_states_) {
    state_list_.push_front(new_state);
  }

  /*while (!state_stack_.empty()) {
      GameState* gs = state_stack_.top();
      Logger::Log("Delete state: " + gs->ToString(), INFO);
      delete gs;
      state_stack_.pop();
      }*/
  return 0;
}

// Maybe remove this?
void Game::Update(const sf::Event &event) {}

void Game::AddState(shared_ptr<GameState> new_state) {
  new_states_.push_front(new_state);
}

Game::~Game() {
  // dtor
}
