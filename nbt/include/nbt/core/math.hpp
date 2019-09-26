#pragma once

/// \file math.hpp
///
/// \brief Contains small functions pertaining to math stuff.

namespace nbt {
namespace core {
/// \brief Useful for computing an arbitrary perpendicular vector
template <class vec3_t> vec3_t createPerpendicularVec3(vec3_t const & vec3) {
  typedef vec3_t::value_type float_t;

  float_t temp = float_t(0.557);

  if (std::fabs(vec3.x) > temp) {
    float_t x = (-vec3.y / vec3.x);
    float_t y = float_t(1.0);
    float_t z = float_t(0.0);

    return vec3_t(x, y, z);
  }

  else if (std::fabs(vec3.y) > temp) {
    float_t x = float_t(1.0);
    float_t y = (-vec3.x / vec3.y);
    float_t z = float_t(0.0);

    return vec3_t(x, y, z);
  }

  else {
    float_t x = float_t(0.0);
    float_t y = float_t(1.0);
    float_t z = (-vec3.y / vec3.y);

    return vec3_t(x, y, z);
  }
}

/// \brief generates nan (not a number) of specified type
template <class C> C nan() {
  return std::numeric_limits<C>::quiet_NaN();
}

/// \brief Tests if a value is nan
template <class C> bool is_nan(C const & c) {
  return c != c;
}
} // namespace core
} // namespace nbt