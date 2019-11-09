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

#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <map>
#include <string>

#include "Parser.hpp"

using std::map;
using std::string;

class ConfigLoader {
 public:
  // Create the ConfigLoader with a given file
  ConfigLoader(string cfg_file_location);

  string GetVar(const string &varname);

  int GetIntVar(const string &varname);

  float GetFloatVar(const string &varname);

  double GetDoubleVar(const string &varname);

  const string cfg_file_location_;

 private:
  Parser config_parser_;
  map<string, string> config_;
};

#endif  // CONFIGLOADER_H
