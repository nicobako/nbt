#pragma once

#include <cstdlib>
#include <string>

#include <nbt/core/ValueRange.hpp>

#include <time.h>

namespace nbt {
namespace core {
/// \brief implementation details of nbt::core
namespace detail {
// These are the functions that do all of the hard work.
// They are hidden within this namespace because,
// as a user, you will never call them directly.
static bool randomSeeded = false;

inline void seedRandomGenerator() {
  std::srand(static_cast<unsigned int>(time(NULL)));

  randomSeeded = true;
}

template <typename T> inline T genRandomValue() {
  if (!randomSeeded)
    seedRandomGenerator();

  return static_cast<T>(rand());
}

template <> inline char genRandomValue() {
  if (!randomSeeded)
    seedRandomGenerator();

  int i = genRandomValue<int>() % (127 - 32) + 32;
  char character(i);
  return character;
}

template <> inline std::string genRandomValue() {
  if (!randomSeeded)
    seedRandomGenerator();

  std::string str;

  int stringLength = 10;
  for (int i = 0; i < stringLength; i++) {
    char character = genRandomValue<char>();
    str += character;
  }
  return str;
}

template <> inline bool genRandomValue() {
  if (!randomSeeded)
    seedRandomGenerator();

  return (genRandomValue<int>() % 2 == 0);
}

template <typename T>
inline T genRandomValue(nbt::core::ValueRange<T> const & range) {
  if (!randomSeeded)
    seedRandomGenerator();

  T randomValueInRange = range.minimum()
                         + static_cast<T>(std::rand())
                               / static_cast<T>(RAND_MAX / range.getSpan());

  return randomValueInRange;
}
} // namespace detail
} // namespace core
} // namespace nbt
