
#include <algorithm>

#include <nbt/ascii/FileReader.hpp>
#include <nbt/ascii/Regex.hpp>
#include <nbt/config/Data.hpp>

namespace nbt {
namespace config {
Data::Data() : sections_() {}

/// \brief Loads all sections from a config file
Data parse_file(std::string const & fileName) {
  Data data;

  // create the ascii file reader
  nbt::ascii::FileReader reader(fileName);

  // make sure tha ini file is opened
  if (!reader.isOpen()) {
    return data;
  }

  /// \note if no section appears in the file then
  /// it will be put into the 'global' section
  std::string sectionName = "global";
  data.add(sectionName);

  auto removeCommentFrom = [](std::string & line) {
    line = line.substr(0, line.find_first_of(";#"));
  };

  auto hasSection = [](std::string const & line) -> bool {
    return (
        line.find("[") != std::string::npos
        && line.find("]") != std::string::npos);
  };

  auto getSectionName = [](std::string const & line) -> std::string {
    auto search_res = nbt::ascii::search(line, "\\[(.*)\\]");
    if (search_res.size() > 1)
      return search_res.at(1);
    else
      return "";
  };

  auto hasProperty = [](std::string const & line) { return !line.empty(); };

  // read the file until the end
  while (!reader.endOfFileReached()) {
    // get the next line
    auto line = reader.getNextLine();

    // check for any comments
    removeCommentFrom(line);

    // trim any spaces from line
    nbt::ascii::trim(line, "\\s\\t");

    // if, after removing comments, line is empty,
    // restart the loop
    if (line.empty())
      continue;

    // if there is a section name in the line, then
    // set sectionName equal to it,
    // else just leave it what it is
    else if (hasSection(line)) {
      sectionName = getSectionName(line);
      data.add(sectionName);
    }

    // if the line has a property,
    // then get its name and value
    else if (hasProperty(line)) {
      auto prop_name = nbt::ascii::search(line, "([^=]*)");

      auto value_name = nbt::ascii::search(line, "=\\s*(.*)");

      std::string propertyName;
      std::string valueName;

      if (prop_name.size() == static_cast<unsigned>(2)) {
        propertyName = prop_name.at(1);
        nbt::ascii::trim(propertyName, "\\s");
      }

      if (value_name.size() == static_cast<unsigned>(2)) {
        valueName = value_name.at(1);
        nbt::ascii::trim(valueName, "\\s");
      }
      data.add(sectionName, propertyName, valueName);
    }
  }

  return data;
}

bool Data::empty() const {
  return this->sections_.empty();
}

bool Data::has(std::string const & sectionName) const {
  auto sectionPos = find_section(sectionName);

  return sectionPos != sections_.end();
}

bool Data::has(
    std::string const & sectionName,
    std::string const & propertyName) const {
  auto sectionPos = find_section(sectionName);

  if (sectionPos == sections_.end()) {
    return false;
  } else {
    return sectionPos->has(propertyName);
  }
}

Section const & Data::section(std::string const & sectionName) const {
  auto sectionPos = this->find_section(sectionName);
  if (sectionPos == sections_.end()) {
    return null_section;
  } else {
    return *sectionPos;
  }
}

std::vector<Section> const & Data::sections() const {
  return sections_;
}

bool Data::add(std::string const & sectionName) {
  if (has(sectionName)) {
    return false;
  } else {
    sections_.emplace_back(Section(sectionName));
    return true;
  }
}

bool nbt::config::Data::add(
    std::string const & sectionName,
    std::string propertyName,
    std::string const & value) {
  this->add(sectionName);

  auto sectionPos = find_section(sectionName);

  return sectionPos->add(Property(propertyName, value));
}

std::vector<Section>::iterator
Data::find_section(std::string const & sectionName) {
  auto sectionPos = std::find_if(
      sections_.begin(),
      sections_.end(),
      [sectionName](Section const & section) -> bool {
        return section.name() == sectionName;
      });

  return sectionPos;
}

std::vector<Section>::const_iterator
Data::find_section(std::string const & sectionName) const {
  auto sectionPos = std::find_if(
      sections_.begin(),
      sections_.end(),
      [sectionName](Section const & section) -> bool {
        return section.name() == sectionName;
      });

  return sectionPos;
}

bool Data::remove(std::string const & sectionName) {
  auto sectionPos = this->find_section(sectionName);

  if (sectionPos == sections_.end()) {
    return false;
  } else {
    sections_.erase(sectionPos);

    return true;
  }
}

bool Data::remove(
    std::string const & sectionName,
    std::string const & propertyName) {
  auto sectionPos = this->find_section(sectionName);

  if (sectionPos == sections_.end()) {
    return false;
  } else {
    return sectionPos->remove(propertyName);
  }
}
} // namespace config
} // namespace nbt
