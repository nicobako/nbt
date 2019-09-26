#include <algorithm>
#include <iterator>

#include <nbt/config/Section.hpp>
#include <nbt/core/random.hpp>

namespace nbt {
namespace config {
Section::Section(std::string const & name) : name_(name), properties_() {}

std::string const & Section::name() const {
  return name_;
}

bool Section::empty() const {
  return properties_.empty();
}

bool Section::add(Property const & property) {
  auto insertion = properties_.insert(property);
  return insertion.second;
}

bool Section::add(
    std::string const & propertyName,
    std::string const & propertyValue) {
  return this->add(Property(propertyName, propertyValue));
}

bool Section::has(Property const & property) const {
  return properties_.find(property) != properties_.end();
}

bool Section::has(std::string const & propertyName) const {
  return has(Property(propertyName, null_property.value()));
}

Property const & Section::property(std::string const & propertyName) const {
  auto propertyPos =
      properties_.find(Property(propertyName, null_property.value()));

  if (propertyPos == properties_.end()) {
    return null_property;
  } else {
    return *propertyPos;
  }
}

std::set<Property> const & Section::properties() const {
  return properties_;
}

bool Section::remove(Property const & property) {
  auto propertyPos = properties_.find(property);

  if (propertyPos == properties_.end()) {
    return false;
  } else {
    properties_.erase(propertyPos);
    return true;
  }
}

bool Section::remove(std::string const & propertyName) {
  return this->remove(Property(propertyName, ""));
}

bool Section::replace(Property const & property) {
  auto propertyPos = properties_.find(property);

  if (propertyPos == properties_.end()) {
    return false;
  } else {
    properties_.erase(propertyPos);
    return add(property);
  }
}
bool operator<(Section const & rhs, Section const & lhs) {
  return rhs.name() < lhs.name();
}

bool operator==(Section const & rhs, Section const & lhs) {
  return rhs.name() == lhs.name();
}
} // namespace config
} // namespace nbt