#include "MainLoop.h"

MainLoop::MainLoop(Player& player, b2World& world) :
  player_(player),
  world_(world) {

}

void MainLoop::Update(const sf::Time& deltaTime, const sf::Event& event) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    player_.ApplyForce(b2Vec2(0, -10));
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    player_.ApplyForce(b2Vec2(0, 10));
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player_.ApplyForce(b2Vec2(-10, 0));
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player_.ApplyForce(b2Vec2(10, 0));
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
    player_.SetRot(player_.GetRot() + 1);
  }

  world_.Step(deltaTime.asSeconds(), 8, 3);
  player_.Update(deltaTime);
}

void MainLoop::Draw(sf::RenderWindow& window) {
  window.draw(player_.GetSprite());
}

MainLoop::~MainLoop() {
  //dtor
}
