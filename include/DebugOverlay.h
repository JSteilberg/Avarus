#ifndef DEBUGOVERLAY_H
#define DEBUGOVERLAY_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

#include "Constants.h"
#include "Logger.h"

using namespace std;

// Represents a collection of useful, constantly updated debug information
// that the game may wish to write to the screen
class DebugOverlay : public sf::Drawable {
public:
  // Construct a DebugOverlay
  DebugOverlay();

  // Inherited from sf::Drawable
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  // Set the display var labeled key to the given value
  void Set(string key, string value);

  // Update the displayed overlay text
  void Update();

  // Flips the active state of the overlay text
  void Toggle();

  // Returns true if the debug overlay is active; false otherwise
  bool IsActive();

  // Set whether the debug overlay is active
  void SetActive(bool active);

private:
  vector<string> msg_order_;

  // Map of message labels to the actual message
  map<string, string> msg_map_;

  // Information to be drawn to overlay
  string msg_;

  // Translucent background to make info stand out
  sf::RectangleShape background_;

  // Text object that is used to draw debug info to screen
  sf::Text info_;

  // Font to draw the debug overlay with
  sf::Font font_;

  bool is_active_ = false;
};

#endif // DEBUGOVERLAY_H
