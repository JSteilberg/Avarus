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
