#include "MainLoop.h"

MainLoop::MainLoop(Player& player, b2World& world) :
  player_(player),
  world_(world) {

}

void MainLoop::Update(const sf::Time& deltaTime, const sf::Event& event) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    player_.AddAcc(Vector2f(0, -4));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    player_.AddAcc(Vector2f(0,  4));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player_.AddAcc(Vector2f(-4, 0));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player_.AddAcc(Vector2f( 4, 0));
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
    player_.AddRot(.1);
  }

  player_.Update(deltaTime);
}

void MainLoop::Draw(sf::RenderWindow& window) {
  window.draw(player_);
}

MainLoop::~MainLoop() {
  //dtor
}
