#ifndef LOGGER_H
#define LOGGER_H

#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <ctime>
#include <iostream>

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
  static void Log(const std::string &msg, SeverityLevel level);

  // Logs (or doesn't) the given information with the given severity level,
  // along with a timestamp
  static void Log(int msgNum, SeverityLevel level);

  // Logs (or doesn't) the given information without any severity level or
  // timestamp
  static void RawLog(const std::string &msg, SeverityLevel level);

  // Returns the current time in m-d-y h:m:s format
  static string TimeStr();

protected:
  // dont you dare
  Logger();

  virtual ~Logger();
};

#endif // LOGGER_H
