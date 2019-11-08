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

#include "Parser.h"

Parser::Parser() {}

Parser::Parser(const char file_name[]) {
  file_name_ = file_name;
  parsed_ = false;
}

void Parser::Parse() {
  try {
    read_json(file_name_, parse_tree_);
  } catch (const json_parser_error &err) {
    // Logger::Log("Failed to parse " + file_name_ + ".", HIGH);
    Logger::Log(err.what(), HIGH);
    parsed_ = false;
    throw err;
  }
  parsed_ = true;
}

const ptree &Parser::GetParseTree() const {
  if (!parsed_) {
    throw new std::runtime_error(
        "Called GetParseTree() before calling Parse()");
  }
  return parse_tree_;
}

Parser::~Parser() {
  // dtor
}
