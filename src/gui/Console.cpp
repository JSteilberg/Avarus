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

Console::Console(LuaHost &lua_host, float x_pos, float y_pos,
                 int line_length = 80, int num_lines = 20, int font_size = 20)
    : lua_host_(lua_host),
      x_pos_(x_pos),
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
      .SetWrapPrefix("> ")
      .SetFitHeightEnabled(true)
      .SetBackgroundColor(sf::Color(100, 135, 105, 200))
      .SetPosition(x_pos, y_pos - edit_box_.GetMaxBoxHeight());

  history_box_.SetDimensions(line_length, num_lines)
      .SetMargins(5.f, 15.f, 5.f, 5.f)
      .SetWrapPrefix("> ")
      .SetFitHeightEnabled(false)
      .SetBackgroundColor(sf::Color(100, 135, 105, 200))
      .SetPosition(x_pos, y_pos - history_box_.GetMaxBoxHeight());

  cursor_clock_.restart();
  cursor_.setPosition(20, 200);
  SetPosition(x_pos, y_pos);
}

void Console::Update() {
  if (cursor_clock_.getElapsedTime().asSeconds() > .5f) {
    blink_on_ = false;
  } else if (cursor_clock_.getElapsedTime().asSeconds() < .5f) {
    blink_on_ = true;
  }
  if (cursor_clock_.getElapsedTime().asSeconds() > 1.0f) {
    cursor_clock_.restart();
  }

  std::list<string> results = lua_host_.GetResults();
  if (!results.empty()) {
    for (auto && result : results) {
      if (result != "") {
        history_box_.AddText(">> " + result+ "\n");
      }
    }
  }

  if (has_update_) {
    history_box_.Update();
    edit_box_.Update();
    cursor_.setPosition(edit_box_.IndexToCoordinates(cursor_pos_));

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
  //Logger::Log(unicode, INFO);
  switch(unicode) {
  case consts::kBackspace:
    if (edit_box_.GetText().size() > 0 && cursor_pos_ > 0) {
      edit_box_.RemoveFrom(cursor_pos_ - 1, 1);
      cursor_pos_--;
    }
    break;

  case consts::kDelete:
    if (edit_box_.GetText().size() > 0 &&
        cursor_pos_ < edit_box_.GetText().size()) {
      edit_box_.RemoveFrom(cursor_pos_, 1);
    }
    break;

  case consts::kCarriageReturn:
  case consts::kNewline:
    if (shift_held) {
      edit_box_.AddText("\r", cursor_pos_);
    } else {
      string text = edit_box_.GetText();
      if (text != "") {
        lua_host_.Script(text);
      }
      history_box_.AddText(text + "\n");
      edit_box_.Clear();
      edit_box_.ReflowText();
      cursor_pos_ = -1;
    }
    cursor_pos_++;
    break;

  case consts::kTab:
    edit_box_.AddText("  ", cursor_pos_);
    cursor_pos_ += 2;
    break;

    // CTRL-l
  case consts::kFF:
    history_box_.AddText(string(num_lines_, '\n'));
    break;

    // CTRL-a
  case consts::kSOH:
    cursor_pos_ = 0;
    break;

    // CTRL-e
  case consts::kENQ:
    cursor_pos_ = edit_box_.GetText().length();
    break;

    // CTRL-f
  case consts::kACK:
    MoveCursor(1);
    break;

    // CTRL-b
  case consts::kSTX:
    MoveCursor(-1);
    break;


  default:
    if (unicode >= 32) {
      edit_box_.AddText(sf::String(unicode).toAnsiString(), cursor_pos_);
      cursor_pos_++;
    }
    break;


  }
  has_update_ = true;
}

void Console::MoveCursor(int amount) {
  if (amount < 0 && amount > -999999 && (size_t)-amount > cursor_pos_) {
    // Bounds checking
    cursor_pos_ = 0;
  } else {
    cursor_pos_ += amount;
  }

  const size_t edit_box_len = edit_box_.GetText().length();
  if (cursor_pos_ > edit_box_len) {
    cursor_pos_ = edit_box_len;
  }

  cursor_clock_.restart();

  has_update_ = true;
}

void Console::Write(sf::String str) {
  edit_box_.AddText(str.toAnsiString(), cursor_pos_);
  cursor_pos_ += str.getSize();
  has_update_ = true;
}
