#include "ConsoleLoop.h"

ConsoleLoop::ConsoleLoop(Game *game) : game_(game) {}

// This is how the main loop do
void ConsoleLoop::Update(const sf::Time &deltaTime, sf::Window &window) {
  HandleKeyEvents(window);

  if (game_->dbg_overlay_.IsActive()) {
    game_->dbg_overlay_.Update();
  }

  game_->console_overlay_.Update();
}

// This is how the drawing do
void ConsoleLoop::Draw(sf::RenderWindow &window) {
  window.draw(game_->console_overlay_);
}

void ConsoleLoop::HandleKeyEvents(sf::Window &window) {
  sf::Event event;

  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
      case sf::Keyboard::F3:
        game_->dbg_overlay_.Toggle();

        // Ya know, sometimes people rail on ternary if statements.
        // Everything in moderation.
        Logger::Log(string("Debug menu turned ") +
                        (game_->dbg_overlay_.IsActive() ? "on" : "off"),
                    INFO);
        break;

      case sf::Keyboard::Escape:
      case sf::Keyboard::BackSlash:
        // Logger::Log(string("Console turned off"), INFO);

        game_->RemoveState(game_->console_loop_);
        break;

      default:
        break;
      }
    }
  }
}

const string ConsoleLoop::ToString() const { return "Console Loop"; }

ConsoleLoop::~ConsoleLoop() {}
