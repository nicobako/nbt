#pragma once

#include <algorithm>
#include <iterator>
#include <sstream>

#include <nbt/ascii/Regex.hpp>

namespace nbt {
namespace ascii {
/// string <--> built-in-type conversions
template <class To, class From> To convert_to(From const & from) {
  std::stringstream ss;
  ss << from;
  To to;
  ss >> to;
  return to;
}

template <class vec_t> vec_t convert_to_vec(std::string const & line) {
  auto line_split = split(line, "\\[\\]\\(\\),\\s\\t");

  vec_t vec;

  for (int i = 0; i < vec.length(); ++i) {
    vec[i] = convert_to<vec_t::value_type>(line_split.at(i));
  }

  return vec;
}

template <class vec_t> bool can_convert_to_vec(std::string const & line) {
  auto line_split = split(line, "\\[\\]\\(\\),\\s\\t");

  vec_t vec;

  if (line_split.size() != vec.length()) {
    return false;
  }

  return std::all_of(
      line_split.begin(),
      line_split.end(),
      can_convert_to<vec_t::value_type, std::string>);
}
/// container-of-string <--> container-of-built-in-types conversions
/// \param from Must be an iterable container
/// \return Type must be a container tha can be passed to std::back_inserter()
template <class To, class From> To convert_all_to(From const & from) {
  To to;

  std::transform(
      from.begin(),
      from.end(),
      std::back_inserter(to),
      convert_to<To::value_type, From::value_type>);

  return to;
}

template <class To, class From> bool can_convert_to(From const & from) {
  std::stringstream ss;
  To to;
  ss << from;
  return (ss >> to) ? true : false;
}

//// Token <--> built-in-type conversions
// template <class To>
// To convert_to(Token const& token)
//{
//	return convert_to<To>(token.str());
//}

/// Converts characters a-z --> A-Z
std::string to_upper(std::string const & str);

/// Converts characters A-Z --> a-z
std::string to_lower(std::string const & str);

} // namespace ascii
} // namespace nbt