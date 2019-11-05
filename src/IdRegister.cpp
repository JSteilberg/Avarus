#include "IdRegister.h"

IdRegister::IdRegister(const string& id_file_) : parser_(id_file_.c_str()) {
  Logger::Log("Parsing ID file", INFO);
  parser_.Parse();

  Logger::Log("Registering IDs", INFO);
  InitializeRegistry();
}

void IdRegister::InitializeRegistry() {
  // Loop through the different id keys and add them to the registry
    for (auto& id_pair : parser_.GetParseTree().get_child("ids")) {
    registry_[id_pair.second.get_value<int>()] = id_pair.first.data();
    inverted_registry_[id_pair.first.data()] = id_pair.second.get_value<int>();
    Logger::RawLog("Registered id " + id_pair.second.data() + " to " + string(id_pair.first.data()), INFO);
  }
}

const string& IdRegister::IdToName(int id) const {
  try {
    return registry_.at(id);
  } catch (std::out_of_range e) {
      Logger::Log("Failed to get name for id " + std::to_string(id), MED);
    return registry_.at(0);
  }
}

int IdRegister::NameToId(const string& name) const {
  try {
    return inverted_registry_.at(name);
  } catch (std::out_of_range e) {
    Logger::Log("Failed to get id for name " + name, MED);
    return inverted_registry_.at("error");
  }
}

IdRegister::~IdRegister() {
  //dtor
}
