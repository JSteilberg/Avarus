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

TextBox::TextBox(const sf::Font &font, int font_size, size_t max_line_length,
                 int max_lines, sf::Color background_color,
                 sf::Color text_color, bool line_wrap, bool fit_height,
                 sf::String wrap_prefix, FlowDirection flow_direction)
    : font_(font),
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
      wrap_prefix_(wrap_prefix),
      flow_direction_(flow_direction),
      text_string_(L""),
      displayed_text_string_(L""),
      text_draw_obj_(),
      background_(),
      current_num_lines_(0),
      has_update_(false) {
  has_update_ = true;
  text_draw_obj_.setFillColor(text_color);
  background_.setFillColor(background_color);
}

void TextBox::SetText(sf::String set_string) {
  Clear();
  AddText(set_string);
  Update();
}

void TextBox::ReflowText() {
  //_text_string_.replace("\a", "");
  size_t first_line_len = FirstEnd(
      text_string_.find("\n"), text_string_.find("\r"), max_line_length_ + 1);
  sf::String right_half;
  if (first_line_len == max_line_length_ + 1) {
    displayed_text_string_ = text_string_.substring(0, first_line_len) + "\a";
    right_half = text_string_.substring(first_line_len);
  } else {
    displayed_text_string_ = text_string_.substring(0, first_line_len + 1);
    right_half = text_string_.substring(first_line_len + 1);
  }

  while (right_half.getSize() > max_line_length_) {
    size_t line_len = FirstEnd(right_half.find("\n"), right_half.find("\r"),
                               max_line_length_ + 1);
    if (line_len == max_line_length_ + 1) {
      displayed_text_string_ += right_half.substring(0, line_len - 1) + "\a";
      right_half = right_half.substring(line_len - 1);
    } else {
      displayed_text_string_ += right_half.substring(0, line_len + 1);
      right_half = right_half.substring(line_len + 1);
    }
  }
  displayed_text_string_ += right_half;
  has_update_ = true;
  Update();
}

void TextBox::RemoveFrom(size_t position, size_t count) {
  sf::String new_text = text_string_;
  new_text.erase(position, count);
  ReflowText();
  has_update_ = true;
  Update();
}

size_t TextBox::FirstEnd(size_t find_1, size_t find_2, size_t max_len) {
  const size_t size_t_max = std::numeric_limits<std::size_t>::max();
  if (find_1 == sf::String::InvalidPos) {
    find_1 = size_t_max;
  }
  if (find_2 == sf::String::InvalidPos) {
    find_2 = size_t_max;
  }
  return std::min(std::min(find_1, find_2), max_len);
}

void TextBox::Update() {
  if (has_update_) {
    ForceUpdate();
  }
}

void TextBox::ForceUpdate() {
  CalcCurrentNumLines();

  const float line_height = font_.getLineSpacing(font_size_);
  // const float char_width = font_.getGlyph(L'_', font_size_, false).advance;

  text_draw_obj_.setFont(font_);
  text_draw_obj_.setCharacterSize(font_size_);
  text_draw_obj_.setString(GetDisplayedText());

  if (flow_direction_ == FROM_BOTTOM) {
    text_draw_obj_.setPosition(
        pos_x_ + left_margin_,
        //          pos_y_ + GetHeight() -
        pos_y_ + line_height * (max_lines_ - current_num_lines_ - 1) +
            top_margin_ - 300);
  } else if (flow_direction_ == FROM_TOP) {
    text_draw_obj_.setPosition(pos_x_ + left_margin_, pos_y_ + top_margin_);
  }

  background_.setPosition(pos_x_, pos_y_);

  background_.setSize(sf::Vector2f(GetWidth(), GetHeight()));
  has_update_ = false;
}

void TextBox::CalcCurrentNumLines() {
  current_num_lines_ = 0;
  for (size_t i = 0; i < displayed_text_string_.getSize(); ++i) {
    // Logger::Log(std::to_string(displayed_text_string_[i]) + "\t" +
    // newline_,
    //             INFO);
    if (displayed_text_string_[i] == newline_) current_num_lines_++;
    if (displayed_text_string_[i] == user_continuation_) current_num_lines_++;
    if (displayed_text_string_[i] == auto_continuation_) current_num_lines_++;
  }
}

void TextBox::AddText(sf::String add_string) {
  ForceUpdate();
  text_string_ += add_string;
  ReflowText();
  ForceUpdate();
}

void TextBox::Clear() {
  text_string_.clear();
  displayed_text_string_.clear();
  text_draw_obj_.setString(L"");
  ForceUpdate();
}

const sf::String &TextBox::GetText() const {
  sf::String ret_str = text_string_;
  ret_str.replace('\r', "\n" + wrap_prefix_);
  return text_string_;
}

sf::String TextBox::GetDisplayedText() const {
  sf::String ret_str = displayed_text_string_;
  ret_str.replace('\a', "\n" + wrap_prefix_);
  ret_str.replace('\r', "\n" + wrap_prefix_);
  return ret_str;
}

const sf::Text &TextBox::GetTextDrawObject() const { return text_draw_obj_; }

void TextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(background_, states);
  target.draw(text_draw_obj_, states);
}

TextBox &TextBox::SetPosition(float pos_x, float pos_y) {
  pos_x_ = pos_x;
  pos_y_ = pos_y;
  ForceUpdate();
  return *this;
}

TextBox &TextBox::SetFontSize(int new_font_size) {
  font_size_ = new_font_size;
  ForceUpdate();
  return *this;
}

TextBox &TextBox::SetBackgroundColor(sf::Color new_color) {
  background_.setFillColor(new_color);
  ForceUpdate();
  return *this;
}

TextBox &TextBox::SetTextColor(sf::Color new_color) {
  text_draw_obj_.setFillColor(new_color);
  ForceUpdate();
  return *this;
}

TextBox &TextBox::SetLineWrapEnabled(bool line_wrap_enabled) {
  line_wrap_ = line_wrap_enabled;
  ForceUpdate();
  return *this;
}

TextBox &TextBox::SetFitHeightEnabled(bool fit_height_enabled) {
  fit_height_ = fit_height_enabled;
  ForceUpdate();
  return *this;
}

TextBox &TextBox::SetWrapPrefix(sf::String new_wrap_prefix) {
  wrap_prefix_ = new_wrap_prefix;
  ForceUpdate();
  return *this;
}

TextBox &TextBox::SetMargins(float left_margin, float right_margin,
                             float bottom_margin, float top_margin) {
  left_margin_ = left_margin;
  right_margin_ = right_margin;
  top_margin_ = top_margin;
  bottom_margin_ = bottom_margin;
  ForceUpdate();
  return *this;
}

TextBox &TextBox::SetDimensions(size_t max_line_length, int max_lines) {
  max_line_length_ = max_line_length;
  max_lines_ = max_lines;
  ForceUpdate();
  return *this;
}

TextBox &TextBox::SetFlowDirection(FlowDirection flow_direction) {
  flow_direction_ = flow_direction;
  ForceUpdate();
  return *this;
}

float TextBox::GetWidth() {
  const float char_width = font_.getGlyph(L'_', font_size_, false).advance;
  return char_width * max_line_length_ + (left_margin_ + right_margin_);
}

float TextBox::GetHeight() {
  CalcCurrentNumLines();

  const float line_height = font_.getLineSpacing(font_size_);

  if (fit_height_) {
    return line_height * current_num_lines_ + (top_margin_ + bottom_margin_);
  } else {
    return line_height * max_lines_ + (top_margin_ + bottom_margin_);
  }
}
