/*             ___
              / | |_   _ ___ _ __ __  __ ____
             / /| | | / /   | `__/ / / /____/
            / / | | |/ / /| | | / /_/ /__\ \
           /_/  |_|___/_/ |_|_| \__,_/_____/

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

#include "DebugOverlay.h"

DebugOverlay::DebugOverlay() : background_(sf::Vector2f(512, 256)) {
  if (!font_.loadFromFile("./res/fonts/Inconsolata.otf")) {
    Logger::Log("Failed to load font", MED);
  } else {
    info_.setFont(font_);
  }

  info_.setPosition(5, 1);
  info_.setCharacterSize(20);
  info_.setFillColor(sf::Color::Black);
  background_.setFillColor(sf::Color(90, 90, 90, 200));
}

void DebugOverlay::Set(string key, string value) {
  // If we haven't set the key before, add it to the end of the
  // display order
  if (!msg_map_.count(key)) {
    msg_order_.push_back(key);
  }
  msg_map_[key] = value;
}

void DebugOverlay::Update() {
  msg_ = "";

  // Loop through the message keys in order and add them to the dbg overlay
  for (size_t i = 0; i < msg_order_.size(); ++i) {
    msg_ = msg_ + msg_map_[msg_order_[i]] + "\n";
  }

  info_.setString(msg_);
}

void DebugOverlay::draw(sf::RenderTarget &target,
                        sf::RenderStates states) const {
  // Draw background rectangle and overlay text
  target.draw(background_, states);
  target.draw(info_, states);
}

// Flips the active state of the overlay text
void DebugOverlay::Toggle() { is_active_ = is_active_ ? false : true; }

// Returns true if the debug overlay is active; false otherwise
bool DebugOverlay::IsActive() { return is_active_; }

// Set whether the debug overlay is active
void DebugOverlay::SetActive(bool active) { is_active_ = active; }
