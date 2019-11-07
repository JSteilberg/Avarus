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

#ifndef LOGGER_H
#define LOGGER_H

#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <ctime>
#include <iostream>
#include <sstream>

#include "Defines.h"

using std::string;

// Passed into the Log function to indicate severity.
enum SeverityLevel {
  // For general information. Only printed if DEBUG_MODE is defined.
  // Prints to cout
  INFO,
  // For small issues that can be effectively mitigated. Only printed if
  // DEBUG_MODE is defined.
  // Prints to cerr
  LOW,
  // For kinda big issues that may be mitigated, but are noticeable and should
  // ultimately not happen.
  // Prints to cerr
  MED,
  // For big issues, usually ones that cannot/shouldn't be recovered from.
  // Prints to cerr
  HIGH
};

// Class for the game's logger. Supports different severity levels for logging
class Logger {
public:
  // Logs (or doesn't) the given information with the given severity level,
  // along with a timestamp
  template <class T> static void Log(const T &msg, SeverityLevel level) {
    std::stringstream ss;
    ss << msg;
    string msg_str = ss.str();

    string logmsg = boost::algorithm::replace_all_copy(
        msg_str, "\n", "\n                        -> ");
    if (level == HIGH) {
      std::cerr << TimeStr() << " [High] " << logmsg << std::endl;
    } else if (level == MED) {
      std::cerr << TimeStr() << " [Med ] " << logmsg << std::endl;
    } else if (level == LOW) {
#ifdef DEBUG_MODE
      std::cerr << TimeStr() << " [Low ] " << logmsg << std::endl;
#endif
    } else if (level == INFO) {
#ifdef DEBUG_MODE
      std::cout << TimeStr() << " [Info] " << logmsg << std::endl;
#endif
    }
  }

  // Logs (or doesn't) the given information without any severity level or
  // timestamp
  template <typename T> static void RawLog(const T &msg, SeverityLevel level) {
    std::stringstream ss;
    ss << msg;
    string msg_str = ss.str();

    string logmsg = "                        -> " +
                    boost::algorithm::replace_all_copy(
                        msg_str, "\n", "\n                        -> ");
    if (level == HIGH) {
      std::cerr << logmsg << std::endl;
    } else if (level == MED) {
      std::cerr << logmsg << std::endl;
    } else if (level == LOW) {
#ifdef DEBUG_MODE
      std::cerr << logmsg << std::endl;
#endif
    } else if (level == INFO) {
#ifdef DEBUG_MODE
      std::cout << logmsg << std::endl;
#endif
    }
  }
  // Returns the current time in m-d-y h:m:s format
  static string TimeStr() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%m-%d-%Y %I:%M:%S", timeinfo);

    return string(buffer);
  }

protected:
  // dont you dare
  Logger();

  virtual ~Logger();
};

#endif // LOGGER_H
