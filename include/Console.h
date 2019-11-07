/*             ___
              / | |_   _ ___ _ __ __  __ ____
             / /| | | / /   | `__/ / / /____/
            / / | | |/ / /| | | / /_/ /__\ \
           /_/  |_|___/_/ |_|_| \__,_/_____/

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

#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "Logger.h"

using std::map;
using std::queue;
using std::string;

class Console : public sf::Drawable {
public:
  // Creates a console at the specified location
  Console(int x_pos, int y_pos, int width, int height);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  void clear();

  void Update();

  void SetPosition(int x_pos, int y_pos);

private:
  const int hratio_ = 20;

  // Holds the command history
  queue<string> history_;

  int x_pos_;
  int y_pos_;

  int width_;
  int height_;

  bool has_update_;

  // Translucent background to make info stand out
  sf::RectangleShape history_background_;

  sf::RectangleShape edit_background_;

  // Text object that is used to draw the console to screen
  sf::Text history_text_;

  // Font to draw the debug overlay with
  sf::Font font_;

  string edit_text_;
};

#endif // CONSOLE_H
