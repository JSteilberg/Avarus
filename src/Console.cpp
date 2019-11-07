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

Console::Console(int x_pos, int y_pos, int width, int height)
    : x_pos_(x_pos), y_pos_(y_pos), width_(width), height_(height),
      has_update_(false), history_background_(sf::Vector2f(width, height)),
      edit_background_(sf::Vector2f(width_, height_ / hratio_)) {

  if (!font_.loadFromFile("./res/fonts/Inconsolata.otf")) {
    Logger::Log("Failed to load font", MED);
  } else {
    history_text_.setFont(font_);
  }

  edit_text_ = "abcdefg";

  SetPosition(x_pos, y_pos);
  history_text_.setCharacterSize(20);
  // font_.setCharacterSize(20);
  history_text_.setFillColor(sf::Color::Black);
  // font_.setFillColor(sf::Color::Black);
  // background_.setPosition(200, 200);
  history_background_.setFillColor(sf::Color(90, 90, 90, 200));
  edit_background_.setFillColor(sf::Color(90, 90, 90, 200));
}

void Console::Update() {
  // string msg_ =

  // Loop through the message keys in order and add them to the dbg overlay
  /*for (size_t i = 0; i < msg_order_.size(); ++i) {
    msg_ = msg_ + msg_map_[msg_order_[i]] + "\n";
  }*/

  if (has_update_) {
    history_text_.setString(edit_text_);

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

void Console::SetPosition(int x_pos, int y_pos) {
  history_text_.setPosition(5, y_pos - height_);
  history_background_.setPosition(0, y_pos - height_);
  edit_background_.setPosition(0, y_pos - (height_ / hratio_));
  has_update_ = true;
}

void Console::UpdateBuffer(sf::Uint32 unicode) {
  edit_text_ += sf::String(unicode);
  has_update_ = true;
}
