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

#include "MainLoop.hpp"

/*MainLoop::MainLoop(Player &player, b2World &world, DebugOverlay &dbg_overlay,
                   Console &console_overlay)
    : player_(player), world_(world), dbg_overlay_(dbg_overlay),
      console_overlay_(console_overlay) {

  console_on_ = false;
  }*/
MainLoop::MainLoop(Game *game)
    : game_(game), update_list_(), console_on_(false) {}

void MainLoop::Update(const sf::Time &deltaTime, sf::Window &window) {
  // TODO: Maybe handling key events should be outside update?
  HandleKeyEvents(window);

  game_->world_.Step(deltaTime.asSeconds(), consts::kVelocityIterations,
                     consts::kPositionIterations);
  game_->player_.Update(deltaTime);

  if (game_->dbg_overlay_.IsActive()) {
    game_->dbg_overlay_.Update();
  }
}

void MainLoop::Draw(sf::RenderWindow &window) {
  window.draw(game_->player_.GetSprite());

  if (game_->dbg_overlay_.IsActive()) {
    window.draw(game_->dbg_overlay_);
  }
}

bool IsKeyPressed(sf::Keyboard::Key key) {
  return sf::Keyboard::isKeyPressed(key);
}

void MainLoop::HandleKeyEvents(sf::Window &window) {
  if (IsKeyPressed(sf::Keyboard::Up) or IsKeyPressed(sf::Keyboard::W)) {
    game_->player_.ApplyForce(b2Vec2(0, -15));
  }

  if (IsKeyPressed(sf::Keyboard::Down) or IsKeyPressed(sf::Keyboard::S)) {
    game_->player_.ApplyForce(b2Vec2(0, 15));
  }

  if (IsKeyPressed(sf::Keyboard::Left) or IsKeyPressed(sf::Keyboard::A)) {
    game_->player_.ApplyForce(b2Vec2(-15, 0));
  }

  if (IsKeyPressed(sf::Keyboard::Right) or IsKeyPressed(sf::Keyboard::D)) {
    game_->player_.ApplyForce(b2Vec2(15, 0));
  }

  if (IsKeyPressed(sf::Keyboard::R)) {
    game_->player_.SetRot(game_->player_.GetRot() + 1);
  }

  sf::Event event;

  while (window.pollEvent(event)) {
    // catch the resize events
    if (event.type == sf::Event::Resized) {
      // update the view to the new size of the window
      sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
      Logger::Log("Resize event", INFO);
      game_->window_.setView(sf::View(visibleArea));
    } else if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
        case sf::Keyboard::Escape:
          window.close();
          break;

        case sf::Keyboard::F3:
          game_->dbg_overlay_.Toggle();

          // Ya know, sometimes people rail on ternary if statements.
          // Everything in moderation.
          Logger::Log(string("Debug menu turned ") +
                          (game_->dbg_overlay_.IsActive() ? "on" : "off"),
                      INFO);
          break;
        case sf::Keyboard::BackSlash:
          game_->window_.setKeyRepeatEnabled(true);
          game_->AddState(game_->console_loop_);
          break;
        case sf::Keyboard::T:
          game_->player_.SetCurrentTexture(
              game_->player_.GetCurrentTexture() == "norm" ? "hurt" : "norm");
          Logger::Log(
              "Set player texture to " + game_->player_.GetCurrentTexture(),
              INFO);
          break;

        default:
          break;
      }
    }
  }
}

const string MainLoop::ToString() const { return "Main Loop"; }

MainLoop::~MainLoop() {
  // dtor
}
