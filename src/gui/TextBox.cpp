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
GNU Affero General Public License for more details.

A copy of the GNU Affero General Public License should accompany
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "TextBox.hpp"

template <typename TString>
TextBox<TString>::TextBox(const sf::Font &font, int font_size, size_t max_line_length,
                 size_t max_lines, sf::Color background_color,
                 sf::Color text_color, bool line_wrap, bool fit_height,
                 FlowDirection flow_direction)
    : font_(font),
      sc_(),
      font_size_(font_size),
      pos_x_(0),
      pos_y_(0),
      left_margin_(0),
      right_margin_(0),
      top_margin_(0),
      bottom_margin_(0),
      max_line_length_(max_line_length),
      max_lines_(max_lines),
      line_wrap_(line_wrap),
      fit_height_(fit_height),
      wrap_prefix_(),
      flow_direction_(flow_direction),
      text_string_(),
      raw_text_string_(),
      text_draw_obj_(),
      background_(),
      current_num_lines_(1),
      has_update_(false) {
  has_update_ = true;
  text_draw_obj_.setFillColor(text_color);
  background_.setFillColor(background_color);
}

template <typename TString>
void TextBox<TString>::SetText(TString set_string) {
  Clear();
  text_string_ = set_string;
  ReflowText();
}

template <typename TString>
void TextBox<TString>::ReflowText() {
  // REFLOW TEXT BEHAVIOR::
  //
  // The text consists of text characters, along with the special characters.
  // To help understand the behavior I am outlining, imagine you are using an
  // instant messaging platform- When you hit enter, you send a message [1].
  // When you hold shift and hit enter, a new line is made but no message is
  // sent [2]. When you type long enough, you go beyond the edge of the text
  // box, but your text simply wraps around and continues on the next line
  // (yet there is no actual new line in the text) [3].
  //
  // 1. '\n' true newline
  //    Fully breaks text, going to next line.
  // 2. '\r' user continuation
  //    Appears identital to [1], but is a different character, enabling
  //    different behavior.
  // 3. '\a' auto continuation
  //    There is no real newline, only visually. Calls to GetText() will have
  //    this character removed. Visually, it will be replaced with a newline and
  //    followed by `wrap_prefix`. Yes I know this is the beep character lol,
  //    someone let me know if it's a bad idea to do this

  const int max_line_length = max_line_length_;
  // Max length of line is reduced if it is a continuation
  // (so that the total line length is still max_line_length)
  const int autocont_max_line_length = max_line_length - wrap_prefix_.length();

  current_num_lines_ = 1;

  TString flowed_string;
  int line_length_counter = 0;
  int current_max_line_length = max_line_length;

  for (size_t i = 0; i < text_string_.length(); ++i) {
    const wchar_t chr = text_string_[i];

    if (chr == sc_.newline_ || chr == sc_.user_continuation_) {
      // 1 and 2 - Both result in passing on the char and resetting the line
      // length counter, as well as setting the max line length to full
      current_max_line_length = max_line_length;
      flowed_string += chr;

      current_num_lines_++;
      line_length_counter = 0;

    } else if (chr == sc_.auto_continuation_) {
      continue;
    } else if (line_length_counter >= current_max_line_length) {
      // If our line was too long, start an auto continuation;
      flowed_string += sc_.auto_continuation_;
      flowed_string += chr;

      // Also remember the length of this line is reduced
      current_max_line_length = autocont_max_line_length;

      // And since we passed through the extra character, the new line length
      // starts at 1
      line_length_counter = 1;

      current_num_lines_++;

    } else {
      flowed_string += chr;
      line_length_counter++;
    }
  }
  // Debugging
  // sf::String sfstr(flowed_string);
  // sfstr.replace("\a", "*");
  // std::cout << sfstr.toAnsiString() << std::endl;

  if (current_num_lines_ > max_lines_) {
    current_num_lines_ = max_lines_;
  }

  raw_text_string_ = flowed_string;
  ForceUpdate();
}

template <typename TString>
void TextBox<TString>::RemoveFrom(size_t position, size_t count) {
  // string new_text = text_string_;
  // new_text.erase(position, count);
  if (position >= text_string_.size()) {
    Logger::Log("Tried to remove from position " + std::to_string(position) +
                    ", but text size is size " +
                    std::to_string(text_string_.size()),
                MED);
    return;
  }
  text_string_ = text_string_.erase(position, count);
  ReflowText();  // Already forces an update
}

template <typename TString>
void TextBox<TString>::Update() {
  if (has_update_) {
    ForceUpdate();
  }
}

template <typename TString>
void TextBox<TString>::ForceUpdate() {
  has_update_ = false;
  //Logger::Log("Update to textbox", INFO);

  text_draw_obj_.setFont(font_);
  text_draw_obj_.setCharacterSize(font_size_);
  text_draw_obj_.setString(GetDisplayedText());

  if (flow_direction_ == FROM_BOTTOM) {
    text_draw_obj_.setPosition(
        pos_x_ + left_margin_,
        pos_y_ + GetMaxBoxHeight() - GetTextHeight() - bottom_margin_);
  } else if (flow_direction_ == FROM_TOP) {
    text_draw_obj_.setPosition(pos_x_ + left_margin_, pos_y_ + top_margin_);
  }

  background_.setPosition(pos_x_, pos_y_ + GetMaxBoxHeight() - GetBoxHeight());
  background_.setSize(sf::Vector2f(GetBoxWidth(), GetBoxHeight()));
}

template <typename TString>
void TextBox<TString>::AddText(TString add_string, int pos) {
  size_t add_pos;
  if (pos < 0) {
    if ((int)text_string_.size() + pos >= 0) {
      add_pos = text_string_.size() + pos + 1;
    } else {
      add_pos = 0;
    }
  } else {
    add_pos = pos;
  }
  // ForceUpdate();
  SetText(text_string_.insert(add_pos, add_string));
}

template <typename TString>
void TextBox<TString>::Clear() {
  text_string_.clear();
  raw_text_string_.clear();
  text_draw_obj_.setString("");
  ForceUpdate();
}

template <typename TString>
const TString TextBox<TString>::GetText() const {
  return text_string_;
}

template <typename TString>
TString TextBox<TString>::GetDisplayedText() const {
  TString ret_str;
  ret_str.reserve(raw_text_string_.length() * 2);

  // Replace all new line types with \n
  for (size_t i = 0; i < raw_text_string_.length(); ++i) {
    if (raw_text_string_[i] == sc_.auto_continuation_) {
      ret_str += sc_.newline_;
      ret_str += wrap_prefix_;
    } else if (raw_text_string_[i] == sc_.user_continuation_ ||
               raw_text_string_[i] == sc_.newline_) {
      ret_str += sc_.newline_;
    } else {
      ret_str += raw_text_string_[i];
    }
  }

  vector<int> newline_positions;
  newline_positions.reserve(max_lines_ * 2);
  newline_positions.push_back(0);

  for (size_t i = 0; i < ret_str.length(); ++i) {
    if (ret_str[i] == sc_.newline_) {
      newline_positions.push_back(i);
    }
  }

  // std::cout << newline_positions.size() << std::endl;
  if (newline_positions.size() > max_lines_) {
    int remove_idx = newline_positions[newline_positions.size() - max_lines_];
    ret_str = ret_str.substr(remove_idx + 1);
  }
  return ret_str;
}

template <typename TString>
sf::Vector2f TextBox<TString>::IndexToCoordinates(size_t index) {
  // const float char_width = font_.getGlyph(L'_', font_size_, false).advance;
  // sf::Vector2f orig_pos = text_draw_obj_.FindCharacterPos(index);

  return text_draw_obj_.findCharacterPos(IndexToDrawnIndex(index));
  // return text_draw_obj_.findCharacterPos(index);
}

template <typename TString>
size_t TextBox<TString>::IndexToDrawnIndex(size_t index) {
  size_t char_counter = 0;
  for (size_t i = 0; i < index; ++i) {
    if (raw_text_string_[i + 1] == sc_.auto_continuation_) {
      // raw_text_string_[i] == sc_.auto_continuation_) {
      // std::cout << wrap_prefix_.length() + 1 << std::endl;
      char_counter += (wrap_prefix_.length() + 1);
      index++;
    } else {
      char_counter++;
    }
  }
  return char_counter;
}

template <typename TString>
const sf::Text &TextBox<TString>::GetTextDrawObject() const { return text_draw_obj_; }

template <typename TString>
void TextBox<TString>::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(background_, states);
  target.draw(text_draw_obj_, states);
}

template <typename TString>
TextBox<TString> &TextBox<TString>::SetPosition(float pos_x, float pos_y) {
  pos_x_ = pos_x;
  pos_y_ = pos_y;
  ForceUpdate();
  return *this;
}

template <typename TString>
TextBox<TString> &TextBox<TString>::SetFontSize(int new_font_size) {
  font_size_ = new_font_size;
  ForceUpdate();
  return *this;
}

template <typename TString>
TextBox<TString> &TextBox<TString>::SetBackgroundColor(sf::Color new_color) {
  background_.setFillColor(new_color);
  ForceUpdate();
  return *this;
}

template <typename TString>
TextBox<TString> &TextBox<TString>::SetTextColor(sf::Color new_color) {
  text_draw_obj_.setFillColor(new_color);
  ForceUpdate();
  return *this;
}

template <typename TString>
TextBox<TString> &TextBox<TString>::SetLineWrapEnabled(bool line_wrap_enabled) {
  line_wrap_ = line_wrap_enabled;
  ForceUpdate();
  return *this;
}

template <typename TString>
TextBox<TString> &TextBox<TString>::SetFitHeightEnabled(bool fit_height_enabled) {
  fit_height_ = fit_height_enabled;
  ForceUpdate();
  return *this;
}

template <typename TString>
TextBox<TString> &TextBox<TString>::SetWrapPrefix(TString new_wrap_prefix) {
  wrap_prefix_ = new_wrap_prefix;
  ForceUpdate();
  return *this;
}

template <typename TString>
TextBox<TString> &TextBox<TString>::SetMargins(float left_margin, float right_margin,
                             float bottom_margin, float top_margin) {
  left_margin_ = left_margin;
  right_margin_ = right_margin;
  top_margin_ = top_margin;
  bottom_margin_ = bottom_margin;
  ForceUpdate();
  return *this;
}

template <typename TString>
TextBox<TString> &TextBox<TString>::SetDimensions(size_t max_line_length, size_t max_lines) {
  max_line_length_ = max_line_length;
  max_lines_ = max_lines;
  ForceUpdate();
  return *this;
}

template <typename TString>
TextBox<TString> &TextBox<TString>::SetFlowDirection(FlowDirection flow_direction) {
  flow_direction_ = flow_direction;
  ForceUpdate();
  return *this;
}

template <typename TString>
float TextBox<TString>::GetBoxWidth() {
  return left_margin_ + GetTextWidth() + right_margin_;
}

template <typename TString>
float TextBox<TString>::GetBoxHeight() {
  if (fit_height_) {
    return top_margin_ + GetTextHeight() + bottom_margin_;
  } else {
    return GetMaxBoxHeight();
  }
}

template <typename TString>
float TextBox<TString>::GetMaxBoxHeight() {
  const float line_height = font_.getLineSpacing(font_size_);
  return top_margin_ + (line_height * max_lines_) + bottom_margin_;
}

template <typename TString>
float TextBox<TString>::GetTextWidth() {
  const float char_width = font_.getGlyph(L'_', font_size_, false).advance;
  return char_width * max_line_length_;
}

template <typename TString>
float TextBox<TString>::GetTextHeight() {
  const float line_height = font_.getLineSpacing(font_size_);
  return line_height * current_num_lines_;
}


template class TextBox<std::wstring>;
template class TextBox<std::string>;
