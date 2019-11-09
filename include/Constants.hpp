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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using std::string;

namespace consts {
// Number of pixels per meter in game
const float kPixelScale = 32.0f;

// Current version of the game... self explanatory
const string kGameVersion = "1.0";

// Target number of game updates per second
const float kUpsPerSec = 100.0f;

// Number of velocity integration iterations to perform per timestep
// Recommended 5-8
const int kVelocityIterations = 6;

// Number of position integration iterations to perform per timestep
// Recommended 2-4
const int kPositionIterations = 2;

// Location of configuration file containing things like graphics params
const string kConfigLocation = "./res/cfg/config.json";

} // namespace consts

#endif // CONSTANTS_H