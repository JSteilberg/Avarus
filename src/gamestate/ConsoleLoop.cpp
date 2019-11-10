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

#include "ConsoleLoop.hpp"
#include <iostream>
ConsoleLoop::ConsoleLoop(Game *game) : game_(game) {
  /*b.SetText(L"1234567890\n123456789012345678901234567890");
  std::cout << "first Displayed\n"
            << tb.GetDisplayedText().toAnsiString() << std::endl;

  tb.SetText(L"1234567\r8901234567890\n123456\n78901234567890");
  std::cout << "Displayed\n"
            << tb.GetDisplayedText().toAnsiString() << std::endl;
  tb.AddText(L"abcdefghijklmnopqrstuvwxyz");
  std::cout << "Now displayed\n"
  << tb.GetDisplayedText().toAnsiString() << std::endl; */
}

// This is how the main loop do
void ConsoleLoop::Update(const sf::Time &deltaTime, sf::Window &window) {
  HandleKeyEvents(window);

  if (game_->dbg_overlay_.IsActive()) {
    game_->dbg_overlay_.Update();
  }

  game_->console_overlay_.Update();
}

// This is how the drawing do
void ConsoleLoop::Draw(sf::RenderWindow &window) {
  window.draw(game_->console_overlay_);
}

void ConsoleLoop::HandleKeyEvents(sf::Window &window) {
  sf::Event event;

  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
        case sf::Keyboard::F3:
          game_->dbg_overlay_.Toggle();

          // Ya know, sometimes people rail on ternary if statements.
          // Everything in moderation.
          Logger::Log(string("Debug menu turned ") +
                          (game_->dbg_overlay_.IsActive() ? "on" : "off"),
                      INFO);
          break;

        case sf::Keyboard::Escape:
          //      case sf::Keyboard::BackSlash:
          // Logger::Log(string("Console turned off"), INFO);
          game_->window_.setKeyRepeatEnabled(false);
          game_->RemoveState(game_->console_loop_);
          return;
          break;

        default:
          break;
      }
    } else if (event.type == sf::Event::TextEntered) {
      game_->console_overlay_.WriteCharacter(event.text.unicode);
    }
  }
}

const string ConsoleLoop::ToString() const { return "Console Loop"; }

ConsoleLoop::~ConsoleLoop() {}
