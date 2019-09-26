#pragma once

/// \file ./random.hpp
/// \brief provides random value generation.
///
/// \class nbt::core::Random
/// \brief not yet implemented
/// \todo Create a class called Random that manages
/// all of the details of seeding the random engine,
/// generating the random values, etc.
/// Perhaps do this by overloading operator()...

#include <nbt/core/detail/random.hpp>

namespace nbt {
namespace core {

/// \brief Generates a random value of type \a T
template <typename T> T random() {
  return detail::genRandomValue<T>();
}

/// \brief Generates a random value of type \a T within the range
template <typename T> T random(nbt::core::ValueRange<T> const & range) {
  return detail::genRandomValue<T>(range);
}
// static const char digits[] = "0123456789";
// static const char minuscule[] = "abcdefghijklmnopqrstuvwxyz";
// static const char majuscule[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
} // namespace core
} // namespace nbt
