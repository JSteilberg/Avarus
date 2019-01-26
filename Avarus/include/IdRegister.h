#ifndef IDREGISTER_H
#define IDREGISTER_H

#include <boost/foreach.hpp>
#include <map>
#include <string>

#include "Logger.h"
#include "Parser.h"

using std::string;
using std::map;

// Used to convert Sprite ID's into names
class IdRegister
{
  public:
    // Create this IdRegister with a given file to use
    IdRegister(const string& id_file);

    // Get a Sprite's name from its id
    const string& IdToName(int id) const;

    // Get a Sprite's id from its name
    // Note: This is much slower then IdToName and really shouldn't be used
    const int NameToId(const string& name) const;

    virtual ~IdRegister();

  protected:

  private:

    // Initializes the registry
    void InitializeRegistry();

    // Holds the file that this IdRegister pulls ids from
    string id_file_;

    // Holds the name corresponding to a given id
    map<int, string> registry_;

    // Used to parse the id file
    Parser parser_;
};

#endif // IDREGISTER_H
