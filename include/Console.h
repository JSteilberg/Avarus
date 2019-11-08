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

#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>
#include <queue>
#include <string>
#include <vector>

#include "Logger.h"

using std::queue;
using std::string;
using std::to_string;

class Console : public sf::Drawable {
public:
  // Creates a console at the specified location
  Console(int x_pos, int y_pos, int width, int height);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  void clear();

  void Update();

  void SetPosition(int x_pos, int y_pos);

  void UpdateBuffer(sf::Uint32 unicode);

private:
  const int text_height_ = 20;
  const int font_size_ = 20;

  // Holds the command history
  queue<string> history_;

  int x_pos_;
  int y_pos_;

  int width_;
  float line_height_;
  int num_lines_;

  bool has_update_;

  // Translucent background to make info stand out
  sf::RectangleShape history_background_;

  sf::RectangleShape edit_background_;

  // Text object that is used to draw the console to screen
  sf::Text history_text_;

  // Font to draw the debug overlay with
  sf::Font font_;

  sf::String edit_text_;

  sf::Clock cursor_clock_;

  bool blink_on_ = false;
};

#endif // CONSOLE_H
