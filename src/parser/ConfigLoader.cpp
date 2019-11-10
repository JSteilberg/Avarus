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

#include <ConfigLoader.hpp>

ConfigLoader::ConfigLoader(string cfg_file_location)
    : cfg_file_location_(cfg_file_location), config_(), err_str_var_("ERR") {
  Logger::Log("Parsing config file '" + cfg_file_location_ + "'", INFO);
  Parser config_parser_(cfg_file_location_);
  config_parser_.Parse();

  for (auto &[variable, setting] : config_parser_.GetParseTree().items()) {
    config_.insert({variable, setting});
    Logger::Log("Registered config " + variable + ": " + setting.get<string>(),
                INFO);
  }

  return;
}

int ConfigLoader::GetIntVar(const string &varname) const {
  if (config_.count(varname)) {
    return std::stoi(config_.at(varname));
  } else {
    Logger::Log("Failed to find element " + varname, MED);
    return -1;
  }
}

float ConfigLoader::GetFloatVar(const string &varname) const {
  if (config_.count(varname)) {
    return std::stof(config_.at(varname));
  } else {
    Logger::Log("Failed to find element " + varname, MED);
    return -1.0f;
  }
}
double ConfigLoader::GetDoubleVar(const string &varname) const {
  if (config_.count(varname)) {
    return std::stod(config_.at(varname));
  } else {
    Logger::Log("Failed to find element " + varname, MED);
    return -1.0;
  }
}

const string &ConfigLoader::GetVar(const string &varname) const {
  if (config_.count(varname)) {
    return config_.at(varname);
  } else {
    Logger::Log("Failed to find element " + varname, MED);
    return err_str_var_;
  }
}
