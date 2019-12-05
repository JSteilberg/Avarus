#ifndef CIVATTRIBUTE_H
#define CIVATTRIBUTE_H

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <limits>
#include <memory>
//#include <json>


namespace wgen {
  // typedef nlohmann::json json;

  using string = std::string;

  template <class T>
  using list = std::list<T>;

  template <class T, class V>
  using map = std::map<T, V>;

  template <class T>
  using unique_ptr = std::unique_ptr<T>;

  class CivAttribute;
  using AttributeMap = map<string, unique_ptr<CivAttribute>>;

class CivAttribute {
protected:
  list<string> parents_;
  list<string> children_;
  list<string> mutexes_;

  CivAttribute(list<string> parents, list<string> children, list<string> mutexes) :
    parents_(parents),
    children_(children),
    mutexes_(mutexes) {}

public:
  CivAttribute() :
    parents_(),
    children_(),
    mutexes_() {}

  virtual string GetName() = 0;

  virtual double OccurrenceProbability(const AttributeMap &current_tags) const = 0;

  virtual bool DependenciesSatisfied(const AttributeMap &potential_tags) const {
    return ContainsAll(potential_tags, GetParents());
  }

  virtual bool MutexesSatisfied(const AttributeMap &current_tags) const {
    return !ContainsAny(current_tags, GetMutexes());
  }

  const list<string> &GetMutexes() const {
    return mutexes_;
  }

  const list<string> &GetParents() const {
    return parents_;
  }

  const list<string> &GetChildren() const {
    return children_;
  }

  inline bool ContainsAll(const AttributeMap &att_map, const list<string> &attributes) const {
    for (string att : attributes) {
      if (att_map.find(att) == att_map.end()) {
        return false;
      }
    }
    return true;
  }

  inline bool ContainsAny(const AttributeMap &att_map, const list<string> &attributes) const {
    for (string att : attributes) {
      if (att_map.find(att) == att_map.end()) {
        return true;
      }
    }
    return false;
  }
};
}

#endif // CIVATTRIBUTE_H
