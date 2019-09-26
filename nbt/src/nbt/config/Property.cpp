#pragma once

#include <nbt/config/Property.hpp>

namespace nbt {
namespace config {
Property::Property(std::string const & name, std::string const & value)
    : name_(name), value_(value) {}

std::string const & Property::name() const {
  return name_;
}
std::string const & Property::value() const {
  return value_;
}

bool operator<(Property const & lhs, Property const & rhs) {
  return lhs.name() < rhs.name();
}

bool operator==(Property const & lhs, Property const & rhs) {
  return lhs.name() == rhs.name() && lhs.value() == rhs.value();
}

bool operator!=(Property const & lhs, Property const & rhs) {
  return !(lhs == rhs);
}

} // namespace config
} // namespace nbt
