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

#include "Console.hpp"

Console::Console(float x_pos, float y_pos, int line_length = 80,
                 int num_lines = 20, int font_size = 20)
    : x_pos_(x_pos),
      y_pos_(y_pos),
      line_length_(line_length),
      line_height_(0),
      num_lines_(num_lines),
      font_size_(font_size),
      has_update_(false),
      font_(),
      history_box_(font_),
      edit_box_(font_),
      cursor_(),
      cursor_clock_(),
      cursor_pos_(0),
      blink_on_(false) {
  if (!font_.loadFromFile("./res/fonts/Hack/Hack.ttf")) {
    Logger::Log("Failed to load font", MED);
  } else {
    // nothing right now
  }

  cursor_.setFont(font_);
  cursor_.setCharacterSize(font_size_);
  cursor_.setString("_");

  line_height_ = font_.getLineSpacing(font_size_);
  // Logger::Log(line_height_, INFO);
  edit_box_.SetDimensions(line_length, num_lines)
      .SetMargins(5.f, 15.f, 3.f, 0.f)
      .SetWrapPrefix(">")
      .SetFitHeightEnabled(true)
      .SetBackgroundColor(sf::Color(90, 90, 90, 200))
      .SetPosition(x_pos, y_pos - edit_box_.GetMaxBoxHeight());

  history_box_.SetDimensions(line_length, num_lines)
      .SetMargins(5.f, 15.f, 5.f, 5.f)
      .SetWrapPrefix(">")
      .SetFitHeightEnabled(false)
      .SetBackgroundColor(sf::Color(90, 90, 90, 200))
      .SetPosition(x_pos, y_pos - history_box_.GetMaxBoxHeight());

  cursor_clock_.restart();
  cursor_.setPosition(20, 200);
  SetPosition(x_pos, y_pos);
}

void Console::Update() {
  history_box_.Update();
  edit_box_.Update();

  if (cursor_clock_.getElapsedTime().asSeconds() < .5f) {
    blink_on_ = false;
  } else if (cursor_clock_.getElapsedTime().asSeconds() > .5f) {
    blink_on_ = true;
  }
  if (cursor_clock_.getElapsedTime().asSeconds() > 1.0f) {
    cursor_clock_.restart();
  }

  cursor_.setPosition(edit_box_.IndexToCoordinates(cursor_pos_));

  if (has_update_) {
    has_update_ = false;
  }
}

void Console::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  // Draw background rectangle and overlay text
  target.draw(history_box_, states);
  target.draw(edit_box_, states);
  if (blink_on_) {
    target.draw(cursor_, states);
  }
}

void Console::SetPosition(float x_pos, float y_pos) {
  /*history_text_.setPosition(x_pos + 5, y_pos - (num_lines_ * line_height_) -
  5); history_background_.setPosition(x_pos, y_pos - (num_lines_ * line_height_)
  - 5); edit_background_.setPosition(x_pos, y_pos - line_height_ - 5);*/
  x_pos_ = x_pos;
  y_pos_ = y_pos;
  has_update_ = true;
}

void Console::WriteCharacter(sf::Uint32 unicode, bool shift_held) {
  if (unicode == sf::String("\b")) {
    if (edit_box_.GetText().size() > 0) {
      edit_box_.RemoveFrom(edit_box_.GetText().size() - 1, 1);
      cursor_pos_--;
    }
  } else if (unicode == sf::String("\r")) {
    cursor_pos_++;

    if (shift_held) {
      edit_box_.AddText("\r");
    } else {
      string text = edit_box_.GetText() + "\n";
      history_box_.AddText(text);
      edit_box_.Clear();
      edit_box_.ReflowText();
      cursor_pos_ = 0;
    }
  } else if (unicode == sf::String("\t")) {
    edit_box_.AddText("  ");
    cursor_pos_ += 2;
  } else {
    cursor_pos_++;
    edit_box_.AddText(sf::String(unicode).toAnsiString(), -1);
  }
  has_update_ = true;
}

void Console::MoveCursor(int amount) {
  cursor_pos_ += amount;
  if (cursor_pos_ < 0) {
    cursor_pos_ = 0;
  }
  has_update_ = true;
}

void Console::Write(sf::String str) {
  edit_box_.AddText(str.toAnsiString());
  has_update_ = true;
}
