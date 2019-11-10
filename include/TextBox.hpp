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

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <limits>

#include "Logger.hpp"

// Direction to move when text
enum FlowDirection { FROM_BOTTOM, FROM_TOP };

// A textbox holds and wraps text automatically. It is able to do this while
// accurately tracking the original text placed into it.
// For a text box, \n represents a new line, whereas \r represents a
// user-created line continuation (think when you press shift+enter in an
// instant message box and instead of sending it creates a newline). Internally,
// \a represents an automatic line continuation created by typing more than
// max_line_length characters
class TextBox : public sf::Drawable {
 public:
  TextBox(const sf::Font &font, int font_size = 20, size_t max_line_length = 80,
          int max_lines = 20, sf::Color background_color = sf::Color::White,
          sf::Color text_color = sf::Color::Black, bool line_wrap = true,
          bool fit_height = false, sf::String wrap_prefix = L"",
          float horizontal_margin = 5, float vertical_margin = 5,
          FlowDirection flow_direction = FROM_BOTTOM);

  void Update();

  void SetText(sf::String set_string);

  void AddText(sf::String add_string);

  void Clear();

  void RemoveFrom(size_t position, size_t count = 1);

  const sf::String &GetText() const;

  sf::String GetDisplayedText() const;

  const sf::Text &GetTextDrawObject() const;

  void SetDimensions(size_t max_line_length, int max_lines);

  void SetLineWrapEnabled(bool line_wrap);

  void SetFlowDirection(FlowDirection flow_direction);

  void ReflowText();

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

 private:
  size_t FirstEnd(size_t find_1, size_t find_2, size_t max_len);

  const sf::Font &font_;
  int font_size_;
  float pos_x_;
  float pos_y_;
  size_t max_line_length_;
  int max_lines_;
  bool line_wrap_;
  bool fit_height_;
  sf::String wrap_prefix_;
  float horizontal_margin_;
  float vertical_margin_;
  FlowDirection flow_direction_;

  sf::String text_string_;
  sf::String displayed_text_string_;

  sf::Text text_draw_obj_;

  sf::RectangleShape background_;

  bool has_update_;
};

#endif  // TEXTBOX_H
