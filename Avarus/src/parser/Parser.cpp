#include "Parser.h"

Parser::Parser() {

}

Parser::Parser(const char file_name[]) {
  file_name_ = file_name;
  parsed_ = false;
}

void Parser::Parse() {
  read_json(file_name_, parse_tree_);
  parsed_ = true;
}

ptree Parser::GetParseTree() {
  if(!parsed_) {
    throw new std::runtime_error("Called GetParseTree before calling Parse()");
  }
  return parse_tree_;
}

Parser::~Parser()
{
  //dtor
}
