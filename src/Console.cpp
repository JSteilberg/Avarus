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

#include "Console.h"

Console::Console(float x_pos, float y_pos, int width, int num_lines)
    : x_pos_(x_pos), y_pos_(y_pos), width_(width), num_lines_(num_lines),
      has_update_(false), history_background_(sf::Vector2f(width, 0)),
      edit_background_(sf::Vector2f(width_, 0)) {

  if (!font_.loadFromFile("./res/fonts/Hack/Hack.ttf")) {
    Logger::Log("Failed to load font", MED);
  } else {
    history_text_.setFont(font_);
  }
  line_height_ = font_.getLineSpacing(font_size_);

  //  edit_text_ = "_";
  cursor_clock_.restart();

  history_text_.setCharacterSize(font_size_);
  history_text_.setFillColor(sf::Color::Black);
  history_text_.setString("_");

  history_background_.setSize(sf::Vector2f(width, num_lines_ * line_height_));
  edit_background_.setSize(sf::Vector2f(width, 1 * line_height_));

  history_background_.setFillColor(sf::Color(90, 90, 90, 200));
  edit_background_.setFillColor(sf::Color(90, 90, 90, 200));

  SetPosition(x_pos, y_pos);
}

void Console::Update() {
  // string msg_ =

  // Loop through the message keys in order and add them to the dbg overlay
  /*for (size_t i = 0; i < msg_order_.size(); ++i) {
    msg_ = msg_ + msg_map_[msg_order_[i]] + "\n";
  }*/

  if (cursor_clock_.getElapsedTime().asSeconds() < .5f) {
    blink_on_ = false;
  } else if (cursor_clock_.getElapsedTime().asSeconds() > .5f) {
    blink_on_ = true;
  }
  if (cursor_clock_.getElapsedTime().asSeconds() > 1.0f) {
    cursor_clock_.restart();
  }

  if (blink_on_) {
    history_text_.setString(edit_text_ + L"_");
  } else {
    history_text_.setString(edit_text_ + L" ");
  }

  if (has_update_) {
    has_update_ = false;
  }
}

void Console::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  // Draw background rectangle and overlay text
  target.draw(history_background_, states);
  target.draw(edit_background_, states);
  target.draw(history_text_, states);
  // target.draw(font_, states);
}

void Console::SetPosition(float x_pos, float y_pos) {
  history_text_.setPosition(x_pos + 5, y_pos - (num_lines_ * line_height_) - 5);
  history_background_.setPosition(x_pos,
                                  y_pos - (num_lines_ * line_height_) - 5);
  edit_background_.setPosition(x_pos, y_pos - line_height_ - 5);
  x_pos_ = x_pos;
  y_pos_ = y_pos;
  has_update_ = true;
}

void Console::WriteCharacter(sf::Uint32 unicode) {
  // Logger::Log(std::string(sf::String(unicode)), INFO);
  if (unicode == sf::String("\b")) {
    if (edit_text_.getSize() > 3 and
        edit_text_.substring(edit_text_.getSize() - 3) == "\n> ") {
      edit_text_ = edit_text_.substring(0, edit_text_.getSize() - 3);
    } else if (edit_text_.getSize() > 4 and
               edit_text_.substring(edit_text_.getSize() - 4, 3) == "\n> ") {
      edit_text_ = edit_text_.substring(0, edit_text_.getSize() - 4);
    } else {
      edit_text_ = edit_text_.substring(0, edit_text_.getSize() - 1);
    }
  } else if (unicode == sf::String("\r")) {
    edit_text_ += "\n";
  } else {
    // Logger::Log("x: " + to_string(history_text_.findCharacterPos(9999).x) +
    //                "y: " + to_string(history_text_.findCharacterPos(9999).y),
    //            INFO);
    edit_text_ += sf::String(unicode);

    if (history_text_.findCharacterPos(999999).x >= (width_ - 10.1) + x_pos_) {
      edit_text_ = edit_text_.substring(0, edit_text_.getSize() - 1) + "\n> " +
                   edit_text_[edit_text_.getSize() - 1];
    }
  }

  if (blink_on_) {
    history_text_.setString(edit_text_ + L"_");
  } else {
    history_text_.setString(edit_text_ + L" ");
  }

  has_update_ = true;
}
