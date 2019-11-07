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
