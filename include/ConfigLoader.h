#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <map>
#include <string>

#include "Parser.h"

using std::map;
using std::string;

class ConfigLoader {
public:
  // Create the ConfigLoader with a given file
  ConfigLoader(const string &cfg_file_location);

  string GetVar(const string &varname);

  int GetIntVar(const string &varname);

  float GetFloatVar(const string &varname);

  double GetDoubleVar(const string &varname);

  const string cfg_file_location_;

private:
  Parser config_parser_;
  map<string, string> config_;
};

#endif // CONFIGLOADER_H
