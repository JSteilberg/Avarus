#include "MainLoop.h"

/*MainLoop::MainLoop(Player &player, b2World &world, DebugOverlay &dbg_overlay,
                   Console &console_overlay)
    : player_(player), world_(world), dbg_overlay_(dbg_overlay),
      console_overlay_(console_overlay) {

  console_on_ = false;
  }*/
MainLoop::MainLoop(shared_ptr<Game> game) : game_(game) { console_on_ = false; }

void MainLoop::Update(const sf::Time &deltaTime, sf::Window &window) {
  // TODO: Maybe handling key events should be outside update?
  HandleKeyEvents(window);

  game_->world_.Step(deltaTime.asSeconds(), consts::kVelocityIterations,
                     consts::kPositionIterations);
  game_->player_.Update(deltaTime);

  if (game_->dbg_overlay_.IsActive()) {
    game_->dbg_overlay_.Update();
  }

  if (console_on_) {
    game_->console_overlay_.Update();
  }
}

void MainLoop::Draw(sf::RenderWindow &window) {
  window.draw(game_->player_.GetSprite());

  if (game_->dbg_overlay_.IsActive()) {
    window.draw(game_->dbg_overlay_);
  }

  if (console_on_) {
    window.draw(game_->console_overlay_);
  }
}

bool IsKeyPressed(sf::Keyboard::Key key) {
  return sf::Keyboard::isKeyPressed(key);
}

void MainLoop::HandleKeyEvents(sf::Window &window) {
  if (IsKeyPressed(sf::Keyboard::Up) or IsKeyPressed(sf::Keyboard::W)) {
    game_->player_.ApplyForce(b2Vec2(0, -15));
  }

  if (IsKeyPressed(sf::Keyboard::Down) or IsKeyPressed(sf::Keyboard::S)) {
    game_->player_.ApplyForce(b2Vec2(0, 15));
  }

  if (IsKeyPressed(sf::Keyboard::Left) or IsKeyPressed(sf::Keyboard::A)) {
    game_->player_.ApplyForce(b2Vec2(-15, 0));
  }

  if (IsKeyPressed(sf::Keyboard::Right) or IsKeyPressed(sf::Keyboard::D)) {
    game_->player_.ApplyForce(b2Vec2(15, 0));
  }

  if (IsKeyPressed(sf::Keyboard::R)) {
    game_->player_.SetRot(game_->player_.GetRot() + 1);
  }

  sf::Event event;

  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
      case sf::Keyboard::Escape:
        window.close();
        break;

      case sf::Keyboard::F3:
        game_->dbg_overlay_.Toggle();

        // Ya know, sometimes people rail on ternary if statements.
        // Everything in moderation.
        Logger::Log(string("Debug menu turned ") +
                        (game_->dbg_overlay_.IsActive() ? "on" : "off"),
                    INFO);
        break;
      case sf::Keyboard::BackSlash:
        console_on_ = !console_on_;
        Logger::Log(string("Console turned ") + (console_on_ ? "on" : "off"),
                    INFO);
        break;
      case sf::Keyboard::T:
        game_->player_.SetCurrentTexture(
            game_->player_.GetCurrentTexture() == "norm" ? "hurt" : "norm");
        Logger::Log("Set player texture to " +
                        game_->player_.GetCurrentTexture(),
                    INFO);
        break;

      default:
        break;
      }
    }
  }
}

const string MainLoop::ToString() const { return "Main Loop"; }

MainLoop::~MainLoop() {
  // dtor
}
