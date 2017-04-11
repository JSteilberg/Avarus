#ifndef PARSER_H
#define PARSER_H

#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <fstream>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::string;

class Parser
{
  public:
    Parser();
    // Initializes the parser with the given file name. Does not actually parse the file.
    Parser(const char file_name[]);
    virtual ~Parser();
    // Returns a boost::property_tree::ptree of the parsed file. Throws exception if called before parse();
    ptree get_parse_tree();
    // Parses the file being held in state
    void parse();

  protected:

  private:
    ptree parse_tree;
    bool parsed;
    string file_name;
};

#endif // PARSER_H
