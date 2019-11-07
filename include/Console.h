#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "Logger.h"

using std::map;
using std::queue;
using std::string;

class Console : public sf::Drawable {
public:
  // Creates a console at the specified location
  Console(int x_pos, int y_pos, int width, int height);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  void clear();

  void Update();

  void SetPosition(int x_pos, int y_pos);

private:
  const int hratio_ = 20;

  // Holds the command history
  queue<string> history_;

  int x_pos_;
  int y_pos_;

  int width_;
  int height_;

  bool has_update_;

  // Translucent background to make info stand out
  sf::RectangleShape history_background_;

  sf::RectangleShape edit_background_;

  // Text object that is used to draw the console to screen
  sf::Text history_text_;

  // Font to draw the debug overlay with
  sf::Font font_;

  string edit_text_;
};

#endif // CONSOLE_H
