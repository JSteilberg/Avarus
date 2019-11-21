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

#define SOL_ALL_SAFETIES_ON 1

#include <SFML/Graphics.hpp>
#include <list>
#include <sol/sol.hpp>
#include <string>
#include <vector>

#include "Logger.hpp"
#include "LuaHost.hpp"
#include "TextBox.hpp"

class TextBox;

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
  Console(LuaHost &lua_host_, float x_pos, float y_pos, int line_length,
          int num_lines, int font_size);

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

  // Adds a single character to the console
  void WriteCharacter(sf::Uint32 unicode, bool shift_held);

  // Writes a string to the console
  void Write(sf::String str);

  // Moves the cursor to the right by amount
  // (or if amount is negative, to the left)
  void MoveCursor(int amount);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

 private:
  LuaHost &lua_host_;

  int x_pos_;
  int y_pos_;

  int line_length_;
  float line_height_;
  int num_lines_;

  int font_size_ = 20;

  bool has_update_;

  // Font to draw the debug overlay with
  sf::Font font_;

  TextBox history_box_;

  TextBox edit_box_;

  sf::Text cursor_;

  sf::Clock cursor_clock_;

  int cursor_pos_;

  bool blink_on_;
};

#endif  // CONSOLE_H
