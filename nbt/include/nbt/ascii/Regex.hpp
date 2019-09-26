#pragma once

#include <deque>
#include <iterator>
#include <regex>
#include <string>

namespace nbt {
namespace ascii {
/// \brief Represents search results
///
/// \todo this should really be renamed,
///  perhaps make a regex_match class...
typedef std::string Token;

/// \brief A contaniner of tokens
///
/// \note I have not yet decided if this should be
/// a std::vector or a std::deque...
typedef std::deque<Token> Tokens;

/// \brief splits line based on delimiter
///
/// \param delimiters a string of
/// all of the possible characters
Tokens
split(std::string const & line, std::string const & delimiters = ",:\\s\\t");

/// \brief Searches a string for a regex
///
/// \return Position 0 of Tokens will
/// store the overall search result.
/// If capture groups are used in the regex then
/// the groups will be in position 1, 2, etc. of Tokens
///
/// This function wraps std::regex_search.
/// Visit http://www.cplusplus.com/reference/regex/regex_search/
/// or http://en.cppreference.com/w/cpp/regex/regex_search
Tokens search(std::string const & line, std::string const & regex);

/// \brief matches a regex
///
/// This function wraps std::regex_match.
/// Visit http://www.cplusplus.com/reference/regex/regex_match/
/// or http://en.cppreference.com/w/cpp/regex/regex_match/
/// for more information.
Tokens match(std::string const & line, std::string const & regex);

/// \brief return all search results in a line
///
/// \return A vector of Tokens.
std::vector<Tokens>
find_all(std::string const & line, std::string const & regex);

/// \brief returns a string with all matches replaced by format
///
/// This function wraps std::regex_replace.
/// Visit http://www.cplusplus.com/reference/regex/regex_replace/
/// or http://en.cppreference.com/w/cpp/regex/regex_replace/
/// for more information.
std::string replace(
    std::string const & line,
    std::string const & regex,
    std::string const & format);

/// \brief Trims characters from beginning and end of a line
void trim(std::string & line, std::string const & characters);

/// \brief joins a container of strings together,
/// with each element of the container separated by \a separation.
template <class Iter>
std::string join(Iter first, Iter second, std::string const & separation) {
  std::string joint_str;
  auto append_to_joint_str = [&joint_str,
                              &separation](std::string const & str) -> void {
    joint_str.append(str);
    joint_str.append(separation);
  };

  std::for_each(first, second, append_to_joint_str);

  // remove the final separation at the end
  joint_str = joint_str.substr(0, joint_str.size() - separation.size());

  return joint_str;
}
} // namespace ascii
} // namespace nbt
