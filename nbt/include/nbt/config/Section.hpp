#pragma once

#include <set>
#include <string>
#include <vector>

#include <nbt/config/Property.hpp>

namespace nbt {
namespace config {
/// \brief represents a section of a config file
///
/// A section has a \a name, and [properties](nbt::config::Property).
/// No two properties may have the same name.
///
/// \see Section::add
class Section {
public:
  /// \brief Section constructor
  ///
  /// \p name The name of the section.
  Section(std::string const & name);

  /// \brief Returns the name of the section.
  std::string const & name() const;

  /// \brief Returns bool indicating if the section has any properties
  bool empty() const;

  /// \brief Adds \p property to the section
  ///
  /// \return Bool indicating if the addition of \p property took place.
  /// \note Properties are compared by name only, not by value.
  bool add(Property const & property);

  /// \brief Adds a property to the section with name = \p propertyName
  /// and value = \p propertyValue.
  bool add(std::string const & propertyName, std::string const & propertyValue);

  /// \brief Checks if a property with the same name as \p property is found in
  /// the section
  bool has(Property const & property) const;

  /// \brief Checks if a property with the same name as \p propertyName is found
  /// in the section
  bool has(std::string const & propertyName) const;

  /// \brief Removes \p property from the section
  ///
  /// \return Bool indicating if removal was performed
  bool remove(Property const & property);

  bool remove(std::string const & propertyName);
  /// \brief Replaces a property in the section with the same name as \p
  /// property \return A bool indicating if the replacement took place
  ///
  /// This will first remove the property with the same name as \p property,
  /// then add \p property in its place.
  /// This function will not perform the addition if a property with the same
  /// name as \p property is not in the section
  bool replace(Property const & property);

  /// \brief Access the property with the associated name \a propertyName
  ///
  /// If the section does not contain the property with the name \p
  /// propertyName, then null_property will be returned
  Property const & property(std::string const & propertyName) const;

  /// \brief Access the list of properties
  std::set<Property> const & properties() const;

private:
  std::string name_;
  std::set<Property> properties_;
};

Section static const null_section("");

bool operator<(Section const & rhs, Section const & lhs);
bool operator==(Section const & rhs, Section const & lhs);
} // namespace config
} // namespace nbt