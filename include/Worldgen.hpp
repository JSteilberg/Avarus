#ifndef WORLDGEN_H
#define WORLDGEN_H

#include <random>
#include <list>
#include <memory>
#include <json/json.hpp>

namespace wgen {
  class CivAttribute;

  using string = std::string;

  template <class T>
  using list = std::list<T>;

  template <class T>
  using shared_ptr = std::shared_ptr<T>;

  using AttributeList = list<shared_ptr<CivAttribute>>;

  using json = nlohmann::json;

  using normal =  std::normal_distribution<double>;
  using gamma = std::gamma_distribution<double>;
  using uniform_real = std::uniform_real_distribution<double>;
  using uniform_int = std::uniform_int_distribution<int>;

  constexpr const static double kLargeNumber = 999999999999999;

  std::mt19937 engine_; // twisted
  uniform_real unitrand_(0.0, 1.0);

  double rand() {
    return unitrand_(engine_);
  }

  double randInt(int low, int high) {
    return uniform_int(low, high-1)(engine_);
  }

  double randInt(int high) {
    return randInt(0, high);
  }


  double clamp(double number, double min, double max=kLargeNumber) {
    if (number > max) {
      return max;
    } else if (number < min) {
      return min;
    } else {
      return number;
    }
  }
}


#endif // WORLDGEN_H
