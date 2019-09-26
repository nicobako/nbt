#pragma once

#include <string>
#include <vector>

#include <nbt/config/Property.hpp>
#include <nbt/config/Section.hpp>
#include <nbt/core/NamedType.hpp>

namespace nbt {
namespace config {
/// \brief parses config files
///
/// Reads and writes .ini formatted files.
/// Supported comment markers are ; and #.
/// \todo Add ability to write config-file to string
/// \todo Should I make this case-insensitive?.
/// \todo Shoul I add ability to modify property values?
///
///
/// .ini file layout :
///   - section (enclosed in brackets : [\<section_name\>]
///   - property
///     - \<name\> = \<value\>
///
/// \note see https://en.wikipedia.org/wiki/INI_file for more info
/// about .ini file format.
class Data {
public:
  /// \brief default ctor
  Data();

  /// \brief Informs if there are any sections in this object
  bool empty() const;

  /// \brief Checks if the sectionName was found in the file.
  bool has(std::string const & sectionName) const;

  /// \brief Checks if the section.property is in the data.
  bool
  has(std::string const & sectionName, std::string const & propertyName) const;

  /// \brief Returns the section with the name \a sectionName
  Section const & section(std::string const & sectionName) const;

  /// \brief returns a list of all sections
  std::vector<Section> const & sections() const;

  /// \brief adds a section with the name \p sectionName
  /// \return Returns a bool indicating if section was added
  bool add(std::string const & sectionName);

  /// \brief adds a property-value to a section
  ///
  /// \returns \a true if the addition took place,
  ///           else returns \false
  bool
  add(std::string const & sectionName,
      std::string propertyName,
      std::string const & value);

  /// \brief removes a section
  ///
  /// \returns \a true if the removal took place,
  ///          else returns \a false.
  bool remove(std::string const & sectionName);

  /// \brief removes a property from a section
  ///
  /// \returns \a true if the removal took place,
  ///          else returns \a false.
  bool
  remove(std::string const & sectionName, std::string const & propertyName);

private:
  std::vector<Section>::iterator find_section(std::string const & sectionName);
  std::vector<Section>::const_iterator
  find_section(std::string const & sectionName) const;

  /// \brief stores the data
  std::vector<Section> sections_;
};

/// \brief Loads all sections from a config file
Data parse_file(std::string const & fileName);
} // namespace config
} // namespace nbt