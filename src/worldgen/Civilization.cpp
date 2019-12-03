#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <map>
#include <string>
#include <json/json.hpp>


class Civilization {
  friend std::ostream& operator<<(std::ostream&, const Civilization&);
  typedef std::normal_distribution<double> normal;
  typedef std::gamma_distribution<double> gamma;
  typedef std::string string;
  typedef nlohmann::json json;
public:
  Civilization(time_t seed=time(NULL)) {
    std::cout << "Using seed " << seed << std::endl;
    engine_.seed(seed);

    GenBasics();
  }

  void GenBasics() {
    normal intelligence_gen(100, 30);
    normal friendliness_gen(100, 80);
    normal emotionality_gen(100, 80);
    normal tribalism_gen(100,25);
    gamma age_gen(5, 8200);

    intelligence_ = Clamp(intelligence_gen(engine_), 0);
    friendliness_ = friendliness_gen(engine_);
    emotionality_ = emotionality_gen(engine_);
    tribalism_ = tribalism_gen(engine_);
    age_ = age_gen(engine_) + 300;
  }

  double Clamp(double number, double min, double max=kLargeNumber) {
    if (number > max) {
      return max;
    } else if (number < min) {
      return min;
    } else {
      return number;
    }
  }

private:
  std::default_random_engine engine_;

  constexpr const static double kLargeNumber = 999999999999999;

  double intelligence_;
  double friendliness_;
  double emotionality_;
  double tribalism_;
  double age_;

  json specifics;
};

std::ostream& operator<<(std::ostream &strm, const Civilization &civ) {
  return strm << "Civilization"
              << "\nintelligence: " << civ.intelligence_
              << "\nfriendliness: " << civ.friendliness_
              << "\nemotionality: " << civ.emotionality_
              << "\ntribalism:    " << civ.tribalism_
              << "\nage:          " << civ.age_ << "\n";
}


int main() {
  for (size_t i = 0; i < 10; ++i) {
    std::cout << Civilization() << std::endl;
  }

}
