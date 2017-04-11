#ifndef PARSER_H
#define PARSER_H

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using std::string;

class Parser
{
  public:
    // Initializes the parser with nothing
    Parser();

    // Initializes the parser with the given file name. Does not actually parse the file.
    Parser(const char file_name[]);

    // Returns a boost::property_tree::ptree of the parsed file. Throws exception if called before parse();
    ptree GetParseTree();

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
