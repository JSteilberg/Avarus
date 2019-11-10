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
GNU Affero General Public License for more details.

A copy of the GNU Affero General Public License should accompany
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <string>
#include <unordered_map>

#include "Parser.hpp"

using std::string;
using std::unordered_map;

class ConfigLoader {
 public:
  // Create the ConfigLoader with a given file
  ConfigLoader(string cfg_file_location);

  // Get a variable from the loaded config as a string
  const string &GetVar(const string &varname) const;

  // Get a variable from the loaded config as an int
  int GetIntVar(const string &varname) const;

  // Get a variable from the loaded config as an float
  float GetFloatVar(const string &varname) const;

  // Get a variable from the loaded config as an double
  double GetDoubleVar(const string &varname) const;

  // Location of the config file
  const string cfg_file_location_;

 private:
  // The actual configuration in 'name: value' format
  unordered_map<string, string> config_;

  // Error string for if we fail to find a variable
  const string err_str_var_;
};

#endif  // CONFIGLOADER_H
