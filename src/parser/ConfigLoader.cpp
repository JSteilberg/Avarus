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

#include <ConfigLoader.h>

ConfigLoader::ConfigLoader(const string &cfg_file_location)
    : cfg_file_location_(cfg_file_location),
      config_parser_(cfg_file_location.c_str()) {

  Logger::Log("Parsing config file '" + cfg_file_location_ + "'", INFO);
  config_parser_.Parse();

  for (auto &config_pair : config_parser_.GetParseTree()) {
    config_.insert({config_pair.first.data(), config_pair.second.data()});
    Logger::Log("Registered config " + string(config_pair.first.data()) + ": " +
                    string(config_pair.second.data()),
                INFO);
  }

  return;
}

int ConfigLoader::GetIntVar(const string &varname) {
  if (config_.count(varname)) {
    return std::stoi(config_.at(varname));
  } else {
    Logger::Log("Failed to find element " + varname, MED);
    return -1;
  }
}

float ConfigLoader::GetFloatVar(const string &varname) {
  if (config_.count(varname)) {
    return std::stof(config_.at(varname));
  } else {
    Logger::Log("Failed to find element " + varname, MED);
    return -1.0f;
  }
}
double ConfigLoader::GetDoubleVar(const string &varname) {
  if (config_.count(varname)) {
    return std::stod(config_.at(varname));
  } else {
    Logger::Log("Failed to find element " + varname, MED);
    return -1.0;
  }
}

string ConfigLoader::GetVar(const string &varname) {
  if (config_.count(varname)) {
    return config_.at(varname);
  } else {
    Logger::Log("Failed to find element " + varname, MED);
    return "ERR";
  }
}
