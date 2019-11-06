#include "Logger.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using std::to_string;

int main() {
  sf::RenderWindow window(sf::VideoMode(100, 100), "Keyboard Printer");
  sf::Event event;

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      sf::Keyboard::Key key;
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        key = sf::Keyboard::Key(event.key.code);
        Logger::Log("Pressed:  " + to_string(key), INFO);
        break;
      case sf::Event::KeyReleased:
        key = sf::Keyboard::Key(event.key.code);
        Logger::Log("Released: " + to_string(key), INFO);
        break;
      default:
        break;
      }
    }
    window.clear();
    window.display();
  }
}
