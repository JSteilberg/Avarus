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
  return std::stoi(config_.at(varname));
}

float ConfigLoader::GetFloatVar(const string &varname) {
  return std::stof(config_.at(varname));
}
double ConfigLoader::GetDoubleVar(const string &varname) {
  return std::stod(config_.at(varname));
}

string ConfigLoader::GetVar(const string &varname) {
  return config_.at(varname);
}
