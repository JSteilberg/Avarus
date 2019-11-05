#include <SFML/Graphics.hpp>
#include <string>
#include "Logger.h"

using std::to_string;

enum Type
  {
    a = 100,
    b = 220,
    c = -1
  };
int main() {
    sf::RenderWindow window(sf::VideoMode(100,100), "Keyboard Printer");

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
