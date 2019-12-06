#ifndef CIVATTRIBUTE_H
#define CIVATTRIBUTE_H

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <limits>
#include <memory>
#include <algorithm>

#include "Logger.hpp"
//#include <json>


namespace wgen {
  // typedef nlohmann::json json;

  using string = std::string;

  template <class T>
  using list = std::list<T>;

  template <class T, class V>
  using map = std::map<T, V>;

  template <class T>
  using shared_ptr = std::shared_ptr<T>;

  class CivAttribute;
  using AttributeList = list<shared_ptr<CivAttribute>>;

class CivAttribute {
protected:
  AttributeList parents_;
  AttributeList children_;
  AttributeList mutexes_;

  list<string> parents_names_;
  list<string> children_names_;
  list<string> mutexes_names_;

  CivAttribute(list<string> parents_names, list<string> children_names, list<string> mutexes_names) :
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

  virtual string GetName() = 0;

  virtual double OccurrenceProbability(AttributeList current_tags) const = 0;

  virtual void InitializeRelationships(AttributeList potential_tags) {
    for (string &parent_name : parents_names_) {
      shared_ptr<CivAttribute> parent = FindAttribute(potential_tags, parent_name);
      if (parent != nullptr) {
        parents_.push_front(parent);
      } else {
        Logger::Log("Failed to find parent CivAttribute " + parent_name, HIGH);
      }
    }
    for (string &child_name : children_names_) {
      shared_ptr<CivAttribute> child = FindAttribute(potential_tags, child_name);
      if (child != nullptr) {
        children_.push_front(child);
      } else {
        Logger::Log("Failed to find child CivAttribute " + child_name, HIGH);
      }
    }
    for (string &mutex_name : mutexes_names_) {
      shared_ptr<CivAttribute> mutex = FindAttribute(potential_tags, mutex_name);
      if (mutex != nullptr) {
        mutexes_.push_front(mutex);
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

  inline bool ContainsAll(AttributeList left, const AttributeList right) const {
    for (auto &att : right) {
      if (!Contains(left, att)) {
        return false;
      }
    }
    return true;
  }

  inline bool ContainsAny(AttributeList left, const AttributeList right) const {
    for (auto &att : right) {
      if (Contains(left, att)) {
        return true;
      }
    }
    return false;
  }

  inline bool Contains(AttributeList att_list, std::shared_ptr<CivAttribute> att) const {
    return std::find(att_list.begin(), att_list.end(), att) != att_list.end();
  }
};
}

#endif // CIVATTRIBUTE_H
