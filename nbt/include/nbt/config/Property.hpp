#pragma once

#include <string>

namespace nbt {
namespace config {
/// \brief represents a property of a section of a .ini file
class Property {
public:
  /// \brief Property constructor
  ///
  /// \param name The name of the property
  /// \param value The value of the property
  Property(std::string const & name, std::string const & value);

  /// \brief Access the name of the property.
  /// \returns The name of the property
  std::string const & name() const;

  /// \brief Accoss the value of the property.
  /// \returns The value of the property
  std::string const & value() const;

private:
  std::string name_;
  std::string value_;
};

/// \brief Compares two properties by name, not by value.
bool operator<(Property const & lhs, Property const & rhs);

/// \brief Equality comparison of two properties.
///
/// Two properties are equal if their name and value is equal
bool operator==(Property const & lhs, Property const & rhs);

bool operator!=(Property const & lhs, Property const & rhs);
/// \brief A \a dummy \a property
static const Property null_property("", "");

} // namespace config
} // namespace nbt