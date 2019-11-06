#include "Parser.h"

Parser::Parser() {}

Parser::Parser(const char file_name[]) {
  file_name_ = file_name;
  parsed_ = false;
}

void Parser::Parse() {
  try {
    read_json(file_name_, parse_tree_);
  } catch (const json_parser_error &err) {
    // Logger::Log("Failed to parse " + file_name_ + ".", HIGH);
    Logger::Log(err.what(), HIGH);
    parsed_ = false;
    throw err;
  }
  parsed_ = true;
}

const ptree &Parser::GetParseTree() const {
  if (!parsed_) {
    throw new std::runtime_error(
        "Called GetParseTree() before calling Parse()");
  }
  return parse_tree_;
}

Parser::~Parser() {
  // dtor
}
