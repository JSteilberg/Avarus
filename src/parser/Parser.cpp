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

#include "Parser.hpp"

Parser::Parser(string file_name)
    : file_name_(file_name), parse_tree_(), parsed_(false) {}

void Parser::Parse() {
  std::ifstream file_stream;
  file_stream.exceptions(std::ifstream::failbit);
  try {
    file_stream.open(file_name_);
  } catch (const std::exception &ex) {
    string err_text = "Parser: Could not find file " + file_name_;
    Logger::Log(err_text, HIGH);
    throw std::runtime_error(err_text);
  }
  try {
    if (file_stream >> parse_tree_) {
      file_stream.close();
    } else {
      Logger::Log("Parser: Could not read " + file_name_, HIGH);
      parsed_ = false;
      file_stream.close();
    }
  } catch (const ParserError &err) {
    Logger::Log("Parser error in '" + file_name_ + "'", HIGH);
    Logger::Log(err.what(), HIGH);
    throw err;
  }

  parsed_ = true;
}

const Json &Parser::GetParseTree() const {
  if (!parsed_) {
    throw std::runtime_error(
        "Called GetParseTree() but have never parsed, or parsing failed!");
  }
  return parse_tree_;
}

Parser::~Parser() {
  // dtor
}
