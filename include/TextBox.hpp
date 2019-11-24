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
#include <string>
#include <vector>

#include "Logger.hpp"

using std::string;
using std::vector;

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
          size_t max_lines = 20, sf::Color background_color = sf::Color::White,
          sf::Color text_color = sf::Color::Black, bool line_wrap = true,
          bool fit_height = false, string wrap_prefix = "",
          FlowDirection flow_direction = FROM_BOTTOM);

  void Update();

  void SetText(string set_string);

  void AddText(string add_string, int pos = -1);

  void Clear();

  void RemoveFrom(size_t position, size_t count = 1);

  const string GetText() const;

  string GetDisplayedText() const;

  const sf::Text &GetTextDrawObject() const;

  TextBox &SetPosition(float pos_x, float pos_y);

  TextBox &SetFontSize(int new_font_size);

  TextBox &SetBackgroundColor(sf::Color new_color);

  TextBox &SetTextColor(sf::Color new_color);

  TextBox &SetLineWrapEnabled(bool line_wrap_enabled);

  TextBox &SetFitHeightEnabled(bool fit_height_enabled);

  TextBox &SetWrapPrefix(string new_wrap_prefix);

  TextBox &SetMargins(float left_margin, float right_margin,
                      float bottom_margin, float top_margin);

  TextBox &SetDimensions(size_t max_line_length, size_t max_lines);

  TextBox &SetFlowDirection(FlowDirection flow_direction);

  // Width of the background box, in pixels
  float GetBoxWidth();

  // Height of the background box, in pixels
  float GetBoxHeight();

  // Width of the text, in pixels [always max width for now]
  float GetTextWidth();

  // Height of the text, in pixels
  float GetTextHeight();

  // Get the max possible height of the box in pixels
  float GetMaxBoxHeight();

  // Re-add line breaks for overflowing text
  void ReflowText();

  // Get the actual coordinates of the character in text_string_, taking into
  // account wrapping and the wrap string
  sf::Vector2f IndexToCoordinates(size_t index);

  size_t IndexToDrawnIndex(size_t index);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

 private:
  // Internal
  void ForceUpdate();

  // Font to draw text with
  const sf::Font &font_;

  // Font size
  int font_size_;

  // Positioning for the text box; text position is determined by
  // both this and the margins
  // This position refers to the window coordinates of the TOP-LEFT corner
  // of the textbox, with no mind to whether fit_height_ is enabled
  float pos_x_;
  float pos_y_;

  // Margins for the text within its box
  float left_margin_;
  float right_margin_;
  float top_margin_;
  float bottom_margin_;

  // Maximum length, in characters, for a line of text in the TextBox
  size_t max_line_length_;

  // Maxinum number of lines in the TextBox
  size_t max_lines_;

  // Do automatic line wrapping?
  bool line_wrap_;

  // Should the height of the TextBox always be max_lines_, or should it
  // stretch to fit the current amount of text
  bool fit_height_;

  // Prefix for wrapped lines
  string wrap_prefix_;

  // Direction to flow multiple lines of text
  FlowDirection flow_direction_;

  // Actual text, corresponds exactly to what the user entered
  string text_string_;

  // Text with auto newlines
  string raw_text_string_;

  // Text with automatic line wrapping
  // string displayed_text_string_;

  // Actual drawable object holding drawn text
  sf::Text text_draw_obj_;

  // Background for the text
  sf::RectangleShape background_;

  // Current number of lines in displayed_text_string_ (!!NOT!! text_string_)
  size_t current_num_lines_;

  // Internal, flag that is set if an update needs to be carried out
  bool has_update_;

  const char newline_ = '\n';
  const char user_continuation_ = '\r';
  const char auto_continuation_ = '\a';
};

#endif  // TEXTBOX_H
