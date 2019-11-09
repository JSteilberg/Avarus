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

#include "IdRegister.hpp"

IdRegister::IdRegister(const string id_file)
    : id_file_(id_file), registry_(), inverted_registry_(), parser_(id_file_) {
  Logger::Log("Parsing ID file '" + id_file + "'", INFO);
  parser_.Parse();

  Logger::Log("Registering IDs", INFO);
  InitializeRegistry();
}

void IdRegister::InitializeRegistry() {
  // Loop through the different id keys and add them to the registry
  for (auto &id_pair : parser_.GetParseTree().get_child("ids")) {
    registry_[id_pair.second.get_value<int>()] = id_pair.first.data();
    inverted_registry_[id_pair.first.data()] = id_pair.second.get_value<int>();
    Logger::RawLog("Registered id " + id_pair.second.data() + " to " +
                       string(id_pair.first.data()),
                   INFO);
  }
}

const string &IdRegister::IdToName(int id) const {
  try {
    return registry_.at(id);
  } catch (std::out_of_range e) {
    Logger::Log("Failed to get name for id " + std::to_string(id), MED);
    return registry_.at(0);
  }
}

int IdRegister::NameToId(const string &name) const {
  try {
    return inverted_registry_.at(name);
  } catch (std::out_of_range e) {
    Logger::Log("Failed to get id for name " + name, MED);
    return inverted_registry_.at("error");
  }
}

IdRegister::~IdRegister() {
  // dtor
}
