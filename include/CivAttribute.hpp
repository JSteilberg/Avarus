#ifndef CIVATTRIBUTE_H
#define CIVATTRIBUTE_H

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <json/json.hpp>

#include "Logger.hpp"
#include "Worldgen.hpp"

namespace wgen {
class CivAttribute {
protected:
  AttributeList parents_;
  AttributeList children_;
  AttributeList mutexes_;

  list<string> parents_names_;
  list<string> children_names_;
  list<string> mutexes_names_;

  CivAttribute(list<string> parents_names, list<string> children_names, list<string> mutexes_names):
    parents_(),
    children_(),
    mutexes_(),
    parents_names_(parents_names),
    children_names_(children_names),
    mutexes_names_(mutexes_names) {}

public:
  CivAttribute() :
    parents_(),
    children_(),
    mutexes_(),
    parents_names_(),
    children_names_(),
    mutexes_names_() {}

  virtual ~CivAttribute() {}

  virtual string GetName() const = 0;

  virtual double OccurrenceProbability(AttributeList current_tags) const = 0;

  virtual void InitializeRelationships(AttributeList potential_tags) {
    for (string &parent_name : parents_names_) {
      shared_ptr<CivAttribute> parent = FindAttribute(potential_tags, parent_name);
      if (parent != nullptr) {
        parents_.push_back(parent);
      } else {
        Logger::Log("Failed to find parent CivAttribute " + parent_name, HIGH);
      }
    }
    for (string &child_name : children_names_) {
      shared_ptr<CivAttribute> child = FindAttribute(potential_tags, child_name);
      if (child != nullptr) {
        children_.push_back(child);
      } else {
        Logger::Log("Failed to find child CivAttribute " + child_name, HIGH);
      }
    }
    for (string &mutex_name : mutexes_names_) {
      shared_ptr<CivAttribute> mutex = FindAttribute(potential_tags, mutex_name);
      if (mutex != nullptr) {
        mutexes_.push_back(mutex);
      } else {
        Logger::Log("Failed to find mutex CivAttribute " + mutex_name, HIGH);
      }
    }
  }

  virtual shared_ptr<CivAttribute> FindAttribute(AttributeList attribute_list, string attribute_name) const {
    for (auto &potential_find : attribute_list) {
      if (potential_find->GetName() == attribute_name) {
        return potential_find;
      }
    }
    return nullptr;
  }

  virtual AttributeList GetUnsatisfiedDependencies(AttributeList current_tags_) const {
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

  const AttributeList &GetMutexes() const {
    return mutexes_;
  }

  const AttributeList &GetParents() const {
    return parents_;
  }

  const AttributeList &GetChildren() const {
    return children_;
  }

  static inline bool ContainsAll(AttributeList left, const AttributeList right) {
    for (auto &att : right) {
      if (!Contains(left, att)) {
        return false;
      }
    }
    return true;
  }

  static inline bool ContainsAny(AttributeList left, const AttributeList right) {
    for (auto &att : right) {
      if (Contains(left, att)) {
        return true;
      }
    }
    return false;
  }

  static inline bool Contains(AttributeList att_list, std::shared_ptr<CivAttribute> att) {
    return std::find(att_list.begin(), att_list.end(), att) != att_list.end();
  }
};

class Eat : public CivAttribute {
public:

  Eat() : CivAttribute({}, {"choke", "fork"}, {}) {}

  string GetName() const override { return "eat"; }

  virtual double OccurrenceProbability(AttributeList current_tags) const override {
    return .8;
  }
};

class Drink : public CivAttribute {
public:

  Drink() : CivAttribute({}, {"choke", "fork"}, {}) {}

  string GetName() const override { return "drink"; }

  double OccurrenceProbability(AttributeList current_tags) const override {
    return .8;
  }

};

class Choke : public CivAttribute {
public:

  Choke() : CivAttribute({"eat", "drink"}, {}, {}) {}

  string GetName() const override { return "choke"; }

  double OccurrenceProbability(AttributeList current_tags) const override {
    return .5;
  }
};

class Fork : public CivAttribute {
public:

  Fork() : CivAttribute({"eat", "drink"}, {"spoon"}, {}) {};

  string GetName() const override { return "fork"; }

  double OccurrenceProbability(AttributeList current_tags) const override {
    return .5;
  }
};

class Spoon : public CivAttribute {
public:
  Spoon() : CivAttribute({"fork"}, {}, {}) {};

  string GetName() const override { return "spoon"; }

  double OccurrenceProbability(AttributeList current_tags) const override {
    return .5;
  }
};

}

std::ostream& operator<<(std::ostream &strm, const wgen::CivAttribute &attribute) {
  return strm << attribute.GetName() << "\n";
}
std::ostream& operator<<(std::ostream &strm, const wgen::shared_ptr<wgen::CivAttribute> &attribute) {
  return strm << attribute->GetName() << "\n";
}


#endif // CIVATTRIBUTE_H
