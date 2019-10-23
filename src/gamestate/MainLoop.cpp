#include "MainLoop.h"

MainLoop::MainLoop(Player& player, b2World& world, DebugOverlay& dbg_overlay) :
  player_(player),
  world_(world),
  dbg_overlay_(dbg_overlay) {

  dbg_menu_on_ = false;
  console_on_  = false;
}

void MainLoop::Update(const sf::Time& deltaTime, sf::Window& window) {
  // TODO: Maybe handling key events should be outside update?
  HandleKeyEvents(window);

  world_.Step(deltaTime.asSeconds(), consts::kVelocityIterations, consts::kPositionIterations);
  player_.Update(deltaTime);

  if(dbg_menu_on_) {
    dbg_overlay_.Update();
  }

}

void MainLoop::Draw(sf::RenderWindow& window) {
  window.draw(player_.GetSprite());

  if(dbg_menu_on_) {
    window.draw(dbg_overlay_);
  }
}

void MainLoop::HandleKeyEvents(sf::Window& window) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    player_.ApplyForce(b2Vec2(0, -15));
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    player_.ApplyForce(b2Vec2(0, 15));
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player_.ApplyForce(b2Vec2(-15, 0));
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player_.ApplyForce(b2Vec2(15, 0));
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
    player_.SetRot(player_.GetRot() + 1);
  }


  sf::Event event;

  while(window.pollEvent(event)) {
    if(event.type == sf::Event::Closed) {
        window.close();
    } else if(event.type == sf::Event::KeyPressed) {
      switch(event.key.code) {
      case sf::Keyboard::Escape:
        window.close();
      case sf::Keyboard::F3:
        dbg_menu_on_ = !dbg_menu_on_;
        // Ya know, sometimes people rail on ternary if statements.
        // Everything in moderation.
        Logger::Log(string("Debug menu turned ") + (dbg_menu_on_ ? "on" : "off"), INFO);
        break;
      case sf::Keyboard::Tilde:
        console_on_ = !console_on_;
        Logger::Log(string("Console turned ") + (console_on_ ? "on" : "off"), INFO);
        break;

        default:
          break;
      }
    }
  }
}

MainLoop::~MainLoop() {
  //dtor
}
