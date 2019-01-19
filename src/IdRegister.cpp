#include "IdRegister.h"

IdRegister::IdRegister(const string& id_file_) : parser_(id_file_.c_str()) {
  Logger::Log("Parsing ID file", INFO);

  parser_.Parse();

  Logger::Log("Registering IDs", INFO);

  InitializeRegistry();
}

void IdRegister::InitializeRegistry() {
  // Loop through the different id keys and add them to the registry
  BOOST_FOREACH(ptree::value_type id_pair, parser_.GetParseTree().get_child("ids")) {
    registry_[id_pair.second.get_value<int>()] = id_pair.first.data();
    Logger::RawLog("Registered id " + id_pair.second.data() + " to " + string(id_pair.first.data()), INFO);
  }
}

const string& IdRegister::IdToName(int id) const {
  try {
    return registry_.at(id);
  } catch(std::out_of_range e) {
    Logger::Log("Failed to get name for id " + id, MED);
    return registry_.at(0);
  }
}

int IdRegister::NameToId(const string& name) const {
  for(const std::pair<int, string>& p : registry_) {
    if(p.second == name) {
      return p.first;
    }
  }
  Logger::Log("Failed to find " + name + " by id.", MED);
  return 0;
}

IdRegister::~IdRegister() {
  //dtor
}
