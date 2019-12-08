#include <string>
#include <random>
#include <chrono>

#include "CivAttribute.hpp"
#include "Worldgen.hpp"


namespace wgen {
class Civilization {
  // I think this is the first time I've ever used friend without feeling bad
  friend std::ostream& operator<<(std::ostream&, const Civilization&);

public:
  Civilization(time_t seed=std::chrono::system_clock::now().time_since_epoch().count()) :
    unitrand_(0.0, 1.0) {

    std::cout << "Seed " << seed << std::endl;
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

    }

    potential_attributes_.push_back(std::make_shared<Eat>());
    potential_attributes_.push_back(std::make_shared<Spoon>());
    potential_attributes_.push_back(std::make_shared<Drink>());
    potential_attributes_.push_back(std::make_shared<Choke>());
    potential_attributes_.push_back(std::make_shared<Fork>());

    std::list<shared_ptr<CivAttribute>> adding_attributes;
    for (shared_ptr<CivAttribute> &att : potential_attributes_) {
      att->InitializeRelationships(potential_attributes_);
      if (att->GetParents().empty()) {
        std::cout << att->GetName() << std::endl;
        adding_attributes.push_back(att);
      }
    }


    while (!adding_attributes.empty()) {
      shared_ptr<CivAttribute> curr_attr = adding_attributes.back();
      adding_attributes.pop_back();

      if (!curr_attr->MutexesSatisfied(current_attributes_)
          || !curr_attr->DependenciesSatisfied(potential_attributes_)) {
         // TODO: Replace with std::erase when it comes out
         auto loc = std::find(potential_attributes_.begin(), potential_attributes_.end(), curr_attr);
         potential_attributes_.erase(loc);
         continue;
       }

       auto unsatisfied_deps = curr_attr->GetUnsatisfiedDependencies(current_attributes_);
       if (unsatisfied_deps.empty()) {
         if (Rand() < curr_attr->OccurrenceProbability(current_attributes_)
             && !CivAttribute::Contains(current_attributes_, curr_attr)) {
           current_attributes_.push_back(curr_attr);
           for (auto &child : curr_attr->GetChildren()) {
             if (!CivAttribute::Contains(adding_attributes, child)) {
               adding_attributes.push_back(child);
             }
           }
         }
       } else {
         for (auto &dep : unsatisfied_deps) {
           if (!CivAttribute::Contains(adding_attributes, dep)) {
             adding_attributes.push_back(dep);
           }
         }
       }
    }

    std::cout << "Attributes: " << std::endl;
    for (auto &att : current_attributes_) {
      std::cout << " " << att;
    }
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

  double RandInt(int high) {
    return RandInt(0, high);
  }

  double RandInt(int low, int high) {
    return uniform_int(low, high-1)(engine_);
  }

private:
  std::mt19937 engine_; // twisted
  uniform_real unitrand_;

  constexpr const static double kLargeNumber = 999999999999999;

  double intelligence_;
  double friendliness_;
  double emotionality_;
  double tribalism_;
  double disgust_;
  double age_;

  AttributeList current_attributes_;
  AttributeList potential_attributes_;
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
