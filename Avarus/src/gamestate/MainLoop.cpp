#include "MainLoop.h"

MainLoop::MainLoop() {
  //ctor
}

MainLoop::MainLoop(Player player) {
  player_ = player;
}

void MainLoop::Update(const sf::Time& deltaTime, const sf::Event& event) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    player_.AddAcc(Vector2f(0, -40));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    player_.AddAcc(Vector2f(0,  40));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player_.AddAcc(Vector2f(-40, 0));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player_.AddAcc(Vector2f( 40, 0));
  }

  player_.Update(deltaTime);
}

void MainLoop::Draw(sf::RenderWindow& window) {
  window.draw(player_);
}

MainLoop::~MainLoop() {
  //dtor
}
