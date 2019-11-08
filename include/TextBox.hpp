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

#include "Logger.hpp"

// Direction to move when text
enum FlowDirection { FROM_BOTTOM, FROM_TOP };

class TextBox : public sf::Drawable {
public:
  TextBox(const sf::Font &font, int font_size = 20, int max_line_length = 80,
          int max_lines = 20,
          sf::Color background_color = sf::Color::Transparent,
          bool line_wrap = true, sf::String wrap_prefix = "",
          FlowDirection flow_direction = FROM_BOTTOM);

  void SetText(sf::String text_string);

  void AddText(sf::String text_string);

  void Clear();

  const sf::String &GetText() const;

  const sf::Text &GetTextDrawObject() const;

  void SetFont(const sf::Font &font);

  void SetDimensions(int max_line_length, int max_lines);

  void SetLineWrapEnabled(bool line_wrap);

  void SetFlowDirection(FlowDirection flow_direction);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

private:
  const sf::Font &font_;
  int font_size_;
  int max_line_length_;
  int max_lines_;
  sf::Color background_color_;
  bool line_wrap_;
  sf::String wrap_prefix_;
  FlowDirection flow_direction_;

  sf::String text_string_;
  sf::String displayed_text_string_;

  sf::Text text_draw_obj_;

  sf::RectangleShape background_;

  bool has_update_ = false;
};

#endif // TEXTBOX_H
