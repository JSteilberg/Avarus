#ifndef IDREGISTER_H
#define IDREGISTER_H

#include <map>
#include <string>

#include "Logger.h"
#include "Parser.h"

using std::map;
using std::string;

// In Avarus, every Sprite has a name and associated ID. These mappings are
// specified in some json file, which is then loaded into the ID registry.
class IdRegister {
public:
  // Create this IdRegister with a given file to use
  IdRegister(const string &id_file);

  // Get a Sprite's name from its id
  const string &IdToName(int id) const;

  // Get a Sprite's id from its name
  int NameToId(const string &name) const;

  virtual ~IdRegister();

protected:
private:
  // Initializes the registry
  void InitializeRegistry();

  // Holds the file that this IdRegister pulls ids from
  string id_file_;

  // Holds the name corresponding to a given id
  map<int, string> registry_;

  // Same as above, but reversed
  map<string, int> inverted_registry_;

  // Used to parse the id file
  Parser parser_;
};

#endif // IDREGISTER_H
