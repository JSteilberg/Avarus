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

#ifndef IDREGISTER_H
#define IDREGISTER_H

#include <map>
#include <string>

#include "Logger.hpp"
#include "Parser.hpp"

using std::map;
using std::string;

// In Avarus, every Sprite has a name and associated ID. These mappings are
// specified in some json file, which is then loaded into the ID registry.
class IdRegister {
 public:
  // Create this IdRegister with a given file to use
  IdRegister(const string id_file);

  // Get a Sprite's name from its id
  const string &IdToName(int id) const;

  // Get a Sprite's id from its name
  int NameToId(const string &name) const;

  virtual ~IdRegister();

 private:
  // Initializes the registry
  void InitializeRegistry();

  // Holds the file that this IdRegister pulls ids from
  string id_file_;

  // Holds the name corresponding to a given id
  map<int, string> registry_;

  // Same as above, but reversed
  map<string, int> inverted_registry_;

  // Used to parse the id file
  Parser parser_;
};

#endif  // IDREGISTER_H
