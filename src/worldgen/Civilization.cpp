#include <chrono>
#include <random>
#include <string>

#include "CivAttribute.hpp"
#include "Worldgen.hpp"

namespace wgen {
class Civilization {
 public:
  Civilization(time_t seed = std::chrono::system_clock::now()
                                 .time_since_epoch()
                                 .count()) {
    std::cout << "Seed " << seed << std::endl;
    engine_.seed(seed);

    // burn card
    engine_.discard(1);

    GenCiv();
  }

  void GenCiv() {
    GenBasics();
    GenRest();
  }

  void GenBasics() {
    potential_attributes_.push_back(std::make_shared<Intelligence>());
    potential_attributes_.push_back(std::make_shared<Emotionality>());
    potential_attributes_.push_back(std::make_shared<Friendliness>());
    potential_attributes_.push_back(std::make_shared<Tribalism>());
    potential_attributes_.push_back(std::make_shared<Disgust>());
    potential_attributes_.push_back(std::make_shared<Age>());
  }

  void GenRest() {
    potential_attributes_.push_back(std::make_shared<CriticalThinking>());
    potential_attributes_.push_back(std::make_shared<Abacus>());

    std::list<shared_ptr<CivAttribute>> adding_attributes;
    for (shared_ptr<CivAttribute> &att : potential_attributes_) {
      att->InitializeRelationships(potential_attributes_);
      if (att->GetParents().empty()) {
        adding_attributes.push_back(att);
      }
    }

    while (!adding_attributes.empty()) {
      shared_ptr<CivAttribute> curr_attr = adding_attributes.back();
      adding_attributes.pop_back();

      if (!curr_attr->MutexesSatisfied(current_attributes_) ||
          !curr_attr->DependenciesSatisfied(potential_attributes_)) {
        // TODO: Replace with std::erase when it comes out
        auto loc = std::find(potential_attributes_.begin(),
                             potential_attributes_.end(), curr_attr);
        potential_attributes_.erase(loc);
        continue;
      }

      auto unsatisfied_deps =
          curr_attr->GetUnsatisfiedDependencies(current_attributes_);
      if (unsatisfied_deps.empty()) {
        if (rand() < curr_attr->OccurrenceProbability(current_attributes_) &&
            !CivAttribute::Contains(current_attributes_, curr_attr)) {
          curr_attr->Occurr(current_attributes_);
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
      std::cout << " " << att->GetName() << std::endl;
    }
  }

  const AttributeList &GetCurrentAttributes() const {
    return current_attributes_;
  }

 private:
  AttributeList current_attributes_;
  AttributeList potential_attributes_;
};

}  // namespace wgen
std::ostream &operator<<(std::ostream &strm, const wgen::Civilization &civ) {
  strm << "Civilization: <naming engine not done yet>\n";
  for (auto &attribute : civ.GetCurrentAttributes()) {
    strm << attribute;
  }
  return strm;
}

int main() {
  for (size_t i = 0; i < 10; ++i) {
    std::cout << wgen::Civilization() << std::endl;
  }
}
