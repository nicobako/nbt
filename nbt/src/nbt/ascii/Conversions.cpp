#include <algorithm>
#include <iterator>

#include <nbt/ascii/Conversions.hpp>

namespace nbt {
namespace ascii {
std::string to_upper(std::string const & str) {
  std::string str_upper;

  std::transform(
      str.begin(), str.end(), std::back_inserter(str_upper), toupper);
  return str_upper;
}

std::string to_lower(std::string const & str) {
  std::string str_lower;

  std::transform(
      str.begin(), str.end(), std::back_inserter(str_lower), tolower);
  return str_lower;
}
} // namespace ascii
} // namespace nbt
