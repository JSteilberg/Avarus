#ifndef CIVATTRIBUTE_H
#define CIVATTRIBUTE_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <json/json.hpp>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "Logger.hpp"
#include "Worldgen.hpp"

namespace wgen {
class CivAttribute {
 protected:
  string name_;

  list<string> parents_names_;
  list<string> children_names_;
  list<string> mutexes_names_;

  AttributeList parents_;
  AttributeList children_;
  AttributeList mutexes_;

  json details_;

  std::function<double(AttributeList &)> prob_func_;

  CivAttribute(string name, list<string> parents_names,
               list<string> children_names, list<string> mutexes_names,
               std::function<double(AttributeList &)> &&prob_func)
      : name_(name),
        parents_names_(parents_names),
        children_names_(children_names),
        mutexes_names_(mutexes_names),
        parents_(),
        children_(),
        mutexes_(),
        details_(),
        prob_func_(prob_func) {}

  CivAttribute(string name, list<string> parents_names,
               list<string> children_names, list<string> mutexes_names)
      : name_(name),
        parents_names_(parents_names),
        children_names_(children_names),
        mutexes_names_(mutexes_names),
        parents_(),
        children_(),
        mutexes_(),
        details_(),
        prob_func_([]([[maybe_unused]] AttributeList &l) -> double {return 1;}){}

  CivAttribute(list<string> parents_names, list<string> children_names,
               list<string> mutexes_names)
      : parents_names_(parents_names),
        children_names_(children_names),
        mutexes_names_(mutexes_names),
        parents_(),
        children_(),
        mutexes_(),
        details_(),
        prob_func_([]([[maybe_unused]] AttributeList &l) -> double {return 1;}) {}

 public:
  CivAttribute()
      : parents_names_(),
        children_names_(),
        mutexes_names_(),
        parents_(),
        children_(),
        mutexes_(),
        details_(),
        prob_func_([]([[maybe_unused]] AttributeList &l) -> double {return 1;}) {}

  virtual ~CivAttribute() {}

  virtual string GetName() const { return name_; }

  virtual void Occurr([[maybe_unused]] AttributeList current_tags) {
    // nothing
  }

  virtual double OccurrenceProbability(AttributeList current_tags) const {
      return prob_func_(current_tags);
  }

  virtual const json &GetDetails() const { return details_; }

  virtual void InitializeRelationships(AttributeList potential_tags) {
    for (string &parent_name : parents_names_) {
      shared_ptr<CivAttribute> parent =
          FindAttribute(potential_tags, parent_name);
      if (parent != nullptr) {
        parents_.push_back(parent);
      } else {
        Logger::Log("Failed to find parent CivAttribute " + parent_name, HIGH);
      }
    }
    for (string &child_name : children_names_) {
      shared_ptr<CivAttribute> child =
          FindAttribute(potential_tags, child_name);
      if (child != nullptr) {
        children_.push_back(child);
      } else {
        Logger::Log("Failed to find child CivAttribute " + child_name, HIGH);
      }
    }
    for (string &mutex_name : mutexes_names_) {
      shared_ptr<CivAttribute> mutex =
          FindAttribute(potential_tags, mutex_name);
      if (mutex != nullptr) {
        mutexes_.push_back(mutex);
      } else {
        Logger::Log("Failed to find mutex CivAttribute " + mutex_name, HIGH);
      }
    }
  }

  static inline shared_ptr<CivAttribute> FindAttribute(AttributeList attribute_list,
                                                 string attribute_name) {
    for (auto &potential_find : attribute_list) {
      if (potential_find->GetName() == attribute_name) {
        return potential_find;
      }
    }
    return nullptr;
  }

  virtual AttributeList GetUnsatisfiedDependencies(
      AttributeList current_tags_) const {
    AttributeList unsatisfied_deps;
    for (auto &dep : GetParents()) {
      if (!Contains(current_tags_, dep)) {
        unsatisfied_deps.push_back(dep);
      }
    }
    return unsatisfied_deps;
  }

  virtual bool DependenciesSatisfied(AttributeList potential_tags) const {
    return ContainsAll(potential_tags, GetParents());
  }

  virtual bool MutexesSatisfied(AttributeList current_tags) const {
    return !ContainsAny(current_tags, GetMutexes());
  }

  const AttributeList &GetMutexes() const { return mutexes_; }

  const AttributeList &GetParents() const { return parents_; }

  const AttributeList &GetChildren() const { return children_; }

  static inline bool ContainsAll(AttributeList left,
                                 const AttributeList right) {
    for (auto &att : right) {
      if (!Contains(left, att)) {
        return false;
      }
    }
    return true;
  }

  static inline bool ContainsAny(AttributeList left,
                                 const AttributeList right) {
    for (auto &att : right) {
      if (Contains(left, att)) {
        return true;
      }
    }
    return false;
  }

  static inline bool Contains(AttributeList att_list,
                              std::shared_ptr<CivAttribute> att) {
    return std::find(att_list.begin(), att_list.end(), att) != att_list.end();
  }
};

class Intelligence : public CivAttribute {
 public:
  Intelligence()
      : CivAttribute("intelligence", {}, {"critical_thinking"}, {}) {}

  string GetName() const override { return "intelligence"; }

  void Occurr([[maybe_unused]] AttributeList current_tags) override {
    normal intelligence_gen(100, 30);
    details_["intelligence"] = clamp(intelligence_gen(engine_), 0);
  }
};

class Emotionality : public CivAttribute {
 public:
  Emotionality() : CivAttribute("emotionality", {}, {}, {}) {}

  void Occurr([[maybe_unused]] AttributeList current_tags) override {
    normal emotionality_gen(100, 80);
    details_["emotionality"] = emotionality_gen(engine_);
  }
};

class Friendliness : public CivAttribute {
 public:
  Friendliness() : CivAttribute("friendliness", {}, {}, {}) {}

  void Occurr([[maybe_unused]] AttributeList current_tags) override {
    normal friendliness_gen(100, 80);
    details_["friendliness"] = friendliness_gen(engine_);
  }
};

class Tribalism : public CivAttribute {
 public:
  Tribalism() : CivAttribute("tribalism", {}, {}, {}) {}

  void Occurr([[maybe_unused]] AttributeList current_tags) override {
    normal tribalism_gen(100, 25);
    details_["tribalism"] = tribalism_gen(engine_);
  }
};

class Disgust : public CivAttribute {
 public:
  Disgust() : CivAttribute("disgust", {}, {}, {}){};

  void Occurr([[maybe_unused]] AttributeList current_tags) override {
    normal disgust_gen(100, 25);
    details_["disgust"] = disgust_gen(engine_);
  }
};

class Age : public CivAttribute {
 public:
  Age() : CivAttribute("age", {}, {}, {}){};

  void Occurr([[maybe_unused]] AttributeList current_tags) override {
    gamma age_gen(2, 8200);
    details_["age"] = age_gen(engine_) + 2000;
  }
};

class CriticalThinking : public CivAttribute {
  public:
  CriticalThinking() :
    CivAttribute("critical_thinking",
    {"intelligence"},
    {"abacus", "biological_computer"},
    {}) {}

    double OccurrenceProbability([[maybe_unused]] AttributeList current_tags) const override {
      auto intel = FindAttribute(current_tags, "intelligence");
      if (intel->GetDetails()["intelligence"] >= 70 || rand() < .8) {
        return 1;
      } else {
        return 0;
      }
    }

    void Occurr([[maybe_unused]] AttributeList current_tags) override {
    }
};

class Abacus : public CivAttribute {
 public:
  Abacus() : CivAttribute("abacus",
    {"critical_thinking"},
    {"mathematics", "mechanical_computer"},
    {/*"biological_computer"*/}) {}

    double OccurrenceProbability([[maybe_unused]] AttributeList current_tags) const override {
      return .8;
    }

    void Occurr([[maybe_unused]] AttributeList current_tags) override {

    }
  };


}  // namespace wgen

std::ostream &operator<<(std::ostream &strm,
                         const wgen::CivAttribute &attribute) {
  return strm << attribute.GetName() << "\n  " << attribute.GetDetails() << "\n";
}
std::ostream &operator<<(
    std::ostream &strm, const wgen::shared_ptr<wgen::CivAttribute> &attribute) {
  return strm << (*attribute);
}

#endif  // CIVATTRIBUTE_H
