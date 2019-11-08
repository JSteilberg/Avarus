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
#include <list>
#include <string>
#include <vector>

#include "Logger.h"

using std::list;
using std::string;
using std::to_string;

/**
 * A Console is a graphical interface in which a user can enter commands.
 *
 * A Console has an edit buffer, where the user can actually type; it can
 * be multiple lines, and is completed when the user hits Return without
 * holding shift.
 *
 * A Console also has a history buffer, which displays previously completed
 * edits, as well as output from executed commands.
 *
 * TODO: Add ability to prevent edit buffer completion if the user has
 * opened some sort of closure e.g. '{' until they close the closure
 */
class Console : public sf::Drawable {
public:
  // Creates a console at the specified location
  // Positioning starts from the bottom left corner.
  Console(float x_pos, float y_pos, int width, int num_lines);

  // Empty the edit buffer without completing it
  void ClearEditBuffer();

  // Completes the edit, returning its text as a string, moving the
  // content to the history buffer, and clearing the edit buffer
  string CompleteEdit();

  // Clears the history buffer
  void ClearHistoryBuffer();

  // Scrolls the history buffer by num_lines lines
  // Positive scrolls up, negative scrolls down
  void ScrollHistoryBuffer(float num_lines);

  // Allow any changes to the buffer from above functions to take effect
  void Update();

  // Sets the position of the bottom-left corner of the buffer
  void SetPosition(float x_pos, float y_pos);

  // Resize the console to be of new width and new number of lines
  void Resize(int new_width, int new_num_lines);

  void WriteCharacter(sf::Uint32 unicode);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

private:
  int text_height_ = 20;
  int font_size_ = 20;

  // Holds the command history
  list<string> history_;

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
