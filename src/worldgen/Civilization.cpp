#include <iostream>
#include <random>
#include <chrono>
#include <list>
#include <map>
#include <string>
#include <json/json.hpp>
#include <limits>
//#include <functional>

class CivAttribute {
protected:
  typedef std::string string;
  typedef nlohmann::json json;
  template <class T>
  using list = std::list<T>;
  template <class T, class V>
  using map = std::map<T, V>;

  using AttributeMap = map<string, CivAttribute>;
public:
  CivAttribute() {}

  virtual string GetName();

  virtual double OccurrenceProbability(AttributeMap current_tags) { return 0; }
  virtual bool DependenciesSatisfied(AttributeMap potential_tags) { return true; }
  virtual bool MutexesSatisfied(AttributeMap current_tags) { return true; }

  virtual list<string> GetParents() { return list<string>(); }
  virtual list<string> GetChildren() { return list<string>(); }
  virtual list<string> GetMutexes() { return list<string>(); }

  bool ContainsAll(AttributeMap att_map, list<string> attributes) {
    for (string att : attributes) {
      if (att_map.find(att) == att_map.end()) {
        return false;
      }
    }
    return true;
  }

  bool ContainsAny(AttributeMap att_map, list<string> attributes) {
    for (string att : attributes) {
      if (att_map.find(att) == att_map.end()) {
        return true;
      }
    }
    return false;
  }
};

class Eat : public CivAttribute {
public:

  Eat() {}

  string GetName() override { return "eat"; }

  double OccurrenceProbability(AttributeMap current_tags) override {
    return .5;
  }

  bool DependenciesSatisfied(AttributeMap potential_tags) override {
    return ContainsAll(potential_tags, GetParents());
  }

  bool MutexesSatisfied(AttributeMap current_tags) override {
    return !ContainsAny(current_tags, GetMutexes());
  }

  list<string> GetMutexes() override {
    return list<string>();
  }

  list<string> GetParents() override {
    return parents_;
  }

  list<string> GetChildren() override {
    return children_;
  }

  list<string> parents_ = {};
  list<string> children_ = {"choke", "fork"};
};

class Drink : public CivAttribute {
public:

  Drink() {}

  string GetName() override { return "drink"; }

  double OccurrenceProbability(AttributeMap current_tags) override {
    return .5;
  }

  bool DependenciesSatisfied(AttributeMap potential_tags) override {
    return ContainsAll(potential_tags, GetParents());
  }

  bool MutexesSatisfied(AttributeMap current_tags) override {
    return !ContainsAny(current_tags, GetMutexes());
  }

  list<string> GetMutexes() override {
    return list<string>();
  }

  list<string> GetParents() override {
    return parents_;
  }

  list<string> GetChildren() override {
    return children_;
  }

  list<string> parents_ = {};
  list<string> children_ = {"choke"};
};

class Choke : public CivAttribute {
public:

  Choke() {}

  string GetName() override { return "choke"; }

  double OccurrenceProbability(AttributeMap current_tags) override {
    return .5;
  }

  bool DependenciesSatisfied(AttributeMap potential_tags) override {
    return ContainsAll(potential_tags, GetParents());
  }

  bool MutexesSatisfied(AttributeMap current_tags) override {
    return !ContainsAny(current_tags, GetMutexes());
  }

  list<string> GetMutexes() override {
    return list<string>();
  }

  list<string> GetParents() override {
    return parents_;
  }

  list<string> GetChildren() override {
    return children_;
  }

  list<string> parents_ = {"eat", "drink"};
  list<string> children_ = {};
};

class Fork : public CivAttribute {
public:

  Fork() {};

  string GetName() override { return "fork"; }

  double OccurrenceProbability(AttributeMap current_tags) override {
    return .5;
  }

  bool DependenciesSatisfied(AttributeMap potential_tags) override {
    return ContainsAll(potential_tags, GetParents());
  }

  bool MutexesSatisfied(AttributeMap current_tags) override {
    return !ContainsAny(current_tags, GetMutexes());
  }

  list<string> GetMutexes() override {
    return list<string>();
  }

  list<string> GetParents() override {
    return parents_;
  }

  list<string> GetChildren() override {
    return children_;
  }

  list<string> parents_ = {"eat"};
  list<string> children_ = {};
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

    potential_attributes_["eat"] = Eat();
    potential_attributes_["drink"] = Drink();
    potential_attributes_["choke"] = Choke();
    potential_attributes_["fork"] = Fork();

    //while (!potential_attributes_.empty()) {
    //   int idx = RandInt(0, potential_attributes_.size());
    //}

    for (int i = 0; i < 100; ++i) {
      std::cout << RandInt(0, 10) << std::endl;
    }

    std::cout << engine_() << "\n" << engine_() << std::endl;
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

  std::map<string, CivAttribute> current_attributes_;
  std::map<string, CivAttribute> potential_attributes_;
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
