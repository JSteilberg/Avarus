#include "Parser.h"

Parser::Parser() {

}

Parser::Parser(const char file_name[]) {
  this->file_name = file_name;
  this->parsed = false;
}

void Parser::parse() {
  read_json (this->file_name, this->parse_tree);
  this->parsed = true;
}

ptree Parser::get_parse_tree() {
  return this->parse_tree;
}

Parser::~Parser()
{
  //dtor
}
