/*             ___
              / | |_   _ ___ _ __ __  __ _____
             / /| | | / /   |  __/ / / /_____/
            / / | | |/ / /| | | / /_/ /__\ \
           /_/  |_|___/_/ |_|_| \____/_____/

Copyright (C) 2019 Jack Steilberg <jsteil123@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Affero General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

A copy of the GNU Affero General Public License should accompany
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

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
