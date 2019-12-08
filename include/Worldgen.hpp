#ifndef WORLDGEN_H
#define WORLDGEN_H

#include <random>
#include <list>
#include <memory>
#include <json/json.hpp>

class CivAttribute;

namespace wgen {
  using string = std::string;

  template <class T>
  using list = std::list<T>;

  //template <class T>
  //using vector = std::vector<T>;

  template <class T>
  using shared_ptr = std::shared_ptr<T>;

  class CivAttribute;
  using AttributeList = list<shared_ptr<CivAttribute>>;

  using json = nlohmann::json;

  typedef std::normal_distribution<double> normal;
  typedef std::gamma_distribution<double> gamma;
  typedef std::uniform_real_distribution<double> uniform_real;
  typedef std::uniform_int_distribution<int> uniform_int;
}


#endif // WORLDGEN_H
