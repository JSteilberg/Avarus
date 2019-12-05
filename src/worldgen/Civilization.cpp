#include <string>
#include <random>
#include <chrono>
#include <json/json.hpp>

#include "CivAttribute.hpp"


namespace wgen {
class Eat : public CivAttribute {
public:

  Eat() : CivAttribute({},{"choke", "fork"}, {}) {}

  string GetName() override { return "eat"; }

  virtual double OccurrenceProbability(const AttributeMap &current_tags) const override {
    return .5;
  }
};

class Drink : public CivAttribute {
public:

  Drink() : CivAttribute({}, {"choke"}, {}) {}

  string GetName() override { return "drink"; }

  double OccurrenceProbability(const AttributeMap &current_tags) const override {
    return .5;
  }

};

class Choke : public CivAttribute {
public:

  Choke() : CivAttribute({}, {"eat", "drink"}, {}) {}

  string GetName() override { return "choke"; }

  double OccurrenceProbability(const AttributeMap &current_tags) const override {
    return .5;
  }
};

class Fork : public CivAttribute {
public:

  Fork() : CivAttribute({}, {"eat"}, {}) {};

  string GetName() override { return "fork"; }

  double OccurrenceProbability(const AttributeMap &current_tags) const override {
    return .5;
  }
};

class Civilization {
  // I think this is the first time I've ever used friend without feeling bad
  friend std::ostream& operator<<(std::ostream&, const Civilization&);

  typedef std::normal_distribution<double> normal;
  typedef std::gamma_distribution<double> gamma;
  typedef std::uniform_real_distribution<double> uniform_real;
  typedef std::uniform_int_distribution<int> uniform_int;
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

  }

  void GenBasics() {
    // god this is actually unbelievably fun
    normal intelligence_gen(100, 30);
    normal friendliness_gen(100, 80);
    normal emotionality_gen(100, 80);
    normal tribalism_gen(100,25);
    normal disgust_gen(100, 25);
    gamma age_gen(2, 8200);

    // no negative intelligence (despite some people I know)
    intelligence_ = Clamp(intelligence_gen(engine_), 0);
    friendliness_ = friendliness_gen(engine_);
    emotionality_ = emotionality_gen(engine_);
    tribalism_ = tribalism_gen(engine_);
    disgust_ = disgust_gen(engine_);
    age_ = age_gen(engine_) + 2000;
  }

  void GenCriticalThinking() {
    if (intelligence_ > 70 || rand() < .05) {
      specifics_["critical_thinking"] = 1;

    }

    potential_attributes_["eat"] = std::make_unique<Eat>();
    potential_attributes_["drink"] = std::make_unique<Drink>();
    potential_attributes_["choke"] = std::make_unique<Choke>();
    potential_attributes_["fork"] = std::make_unique<Fork>();

    //while (!potential_attributes_.empty()) {
    //   int idx = RandInt(0, potential_attributes_.size());
    //}
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

  double RandInt(int low, int high) {
    return uniform_int(low, high-1)(engine_);
  }

private:
  std::mt19937 engine_;
  uniform_real unitrand_;

  constexpr const static double kLargeNumber = 999999999999999;

  double intelligence_;
  double friendliness_;
  double emotionality_;
  double tribalism_;
  double disgust_;
  double age_;

  json specifics_;

  AttributeMap current_attributes_;
  AttributeMap potential_attributes_;
};



std::ostream& operator<<(std::ostream &strm, const Civilization &civ) {
  return strm << "Civilization"
              << "\nintelligence: " << civ.intelligence_
              << "\nfriendliness: " << civ.friendliness_
              << "\nemotionality: " << civ.emotionality_
              << "\ntribalism:    " << civ.tribalism_
              << "\nage:          " << civ.age_ << "\n";
}
}


int main() {
  for (size_t i = 0; i < 10; ++i) {
    std::cout << wgen::Civilization() << std::endl;
  }

}
