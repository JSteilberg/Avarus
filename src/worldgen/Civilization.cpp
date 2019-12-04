#include <iostream>
#include <random>
#include <chrono>
#include <map>
#include <string>
#include <json/json.hpp>


class Civilization {
  // I think this is the first time I've ever used friend without feeling bad
  friend std::ostream& operator<<(std::ostream&, const Civilization&);

  typedef std::normal_distribution<double> normal;
  typedef std::gamma_distribution<double> gamma;
  typedef std::uniform_real_distribution<double> uniform;
  typedef std::string string;
  typedef nlohmann::json json;
public:
  Civilization(time_t seed=std::chrono::system_clock::now().time_since_epoch().count()) :
    unitrand_(0.0, 1.0) {

    std::cout << "Using seed " << seed << std::endl;
    engine_.seed(seed);

    // burn card
    engine_.discard(1);

    GenCiv();
  }

  void GenCiv() {
    GenBasics();
    GenCriticalThinking();
    GenSpeech();
    GenGovernment();
    GenRelations();
    GenAppearance();

  }

  void GenBasics() {
    // god this is actually unbelievably fun
    normal intelligence_gen(100, 30);
    normal friendliness_gen(100, 80);
    normal emotionality_gen(100, 80);
    normal tribalism_gen(100,25);
    gamma age_gen(2, 8200);

    // no negative intelligence (despite some people I know)
    intelligence_ = Clamp(intelligence_gen(engine_), 0);
    friendliness_ = friendliness_gen(engine_);
    emotionality_ = emotionality_gen(engine_);
    tribalism_ = tribalism_gen(engine_);
    age_ = age_gen(engine_) + 2000;
  }

  void GenCriticalThinking() {
    if (intelligence_ > 70 || rand() < .05) {
      specifics_["critical_thinking"] = 1;
    }
    std::cout << engine_() << "\n" << engine_() << std::endl;
  }

  void GenSpeech() {

  }

  void GenGovernment() {

  }

  void GenRelations() {

  }

  void GenAppearance() {

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

  double Rand() {
    return unitrand_(engine_);
  }

private:
  std::mt19937 engine_;
  uniform unitrand_;

  constexpr const static double kLargeNumber = 999999999999999;

  double intelligence_;
  double friendliness_;
  double emotionality_;
  double tribalism_;
  double age_;

  json specifics_;
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
