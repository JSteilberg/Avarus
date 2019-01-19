#include "Logger.h"

Logger::Logger() {
  //ctor
}

void Logger::Log(const string& msg, SeverityLevel level) {
  string logmsg = boost::algorithm::replace_all_copy(msg, "\n", "\n                        -> ");
  if (level == HIGH) {
    std::cerr << TimeStr() << " [High] " << logmsg << std::endl;
  } else if (level == MED) {
    std::cerr << TimeStr() << " [Med ] " << logmsg << std::endl;
  } else if (level == LOW) {
#ifdef DEBUG_MODE
    std::cerr << TimeStr() << " [Low ] " << logmsg << std::endl;
#endif
  } else if (level == INFO) {
#ifdef DEBUG_MODE
    std::cout << TimeStr() << " [Info] " << logmsg << std::endl;
#endif
  }
}

void Logger::Log(int msgNum, SeverityLevel level) {
  Log(boost::lexical_cast<string>(msgNum), level);
}

void Logger::RawLog(const string& msg, SeverityLevel level) {
  string logmsg = "                        -> " +
                  boost::algorithm::replace_all_copy(msg, "\n", "\n                        -> ");
  if (level == HIGH) {
    std::cerr << logmsg << std::endl;
  } else if (level == MED) {
    std::cerr << logmsg << std::endl;
  } else if (level == LOW) {
#ifdef DEBUG_MODE
    std::cerr << logmsg << std::endl;
#endif
  } else if (level == INFO) {
#ifdef DEBUG_MODE
    std::cout << logmsg << std::endl;
#endif
  }
}

string Logger::TimeStr() {
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%m-%d-%Y %I:%M:%S", timeinfo);

  return string(buffer);
}

Logger::~Logger() {
  //dtor
}
