#include <ConfigLoader.h>

ConfigLoader::ConfigLoader(const string &cfg_file_location)
    : cfg_file_location_(cfg_file_location),
      config_parser_(cfg_file_location.c_str()) {

  Logger::Log("Parsing config file '" + cfg_file_location_ + "'", INFO);
  config_parser_.Parse();

  for (auto &config_pair : config_parser_.GetParseTree()) {
    Logger::Log(config_pair.first.data(), INFO);
  }

  return;
}
