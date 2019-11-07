#include "Console.h"

Console::Console() : background_(sf::Vector2f(512, 256)),
                     msg_("TEST TEST TEST TEST TEST TEST TEST") {
  if (!font_.loadFromFile("./res/fonts/Inconsolata.otf")) {
    Logger::Log("Failed to load font", MED);
  } else {
    info_.setFont(font_);
  }

  info_.setPosition(100, 10);
  info_.setCharacterSize(20);
  info_.setFillColor(sf::Color::Black);
  background_.setPosition(200,200);
  background_.setFillColor(sf::Color(90, 90, 90, 200));
}


void Console::Update() {
    //string msg_ = 

  // Loop through the message keys in order and add them to the dbg overlay
  /*for (size_t i = 0; i < msg_order_.size(); ++i) {
    msg_ = msg_ + msg_map_[msg_order_[i]] + "\n";
  }*/

  info_.setString(msg_);
}

void Console::draw(sf::RenderTarget &target,
                   sf::RenderStates states) const {
  // Draw background rectangle and overlay text
  target.draw(background_, states);
  target.draw(info_, states);
}
