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

#ifndef PARSER_H
#define PARSER_H

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Logger.h"

using boost::property_tree::json_parser_error;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using std::string;

class Parser {
public:
  // Initializes the parser with nothing
  Parser();

  // Initializes the parser with the given file name. Does not actually parse
  // the file.
  Parser(const char file_name[]);

  // Returns a boost::property_tree::ptree of the parsed file. Throws exception
  // if called before parse();
  const ptree &GetParseTree() const;

  // Parses the file being held in state
  void Parse();

  virtual ~Parser();

protected:
private:
  ptree parse_tree_;
  bool parsed_;
  string file_name_;
};

#endif // PARSER_H
