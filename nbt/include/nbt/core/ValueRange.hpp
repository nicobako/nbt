#pragma once

#include <algorithm> // std::min, std::max
#include <vector>

#include <nbt/core/NamedType.hpp>

namespace nbt {
namespace core {
/// \brief represents a range of values.
///
/// The class nbt::ValueRange allows users to specify
/// the minimum and maximum values of a range of values
///
/// \note The bounds are inclusive of the values the user
/// sets as the minimum and maximum, meaning that if you set
/// the minimum to 0, and the maximum to 10,
/// 0 and 10 are in the range,
/// -1 and 11 are out of the range.
template <typename T> class ValueRange {
public:
  /// \brief default ctor
  ValueRange(T first, T second) : first_(first), second_(second) {}
  /// \brief Returns the first value used in the ctor.
  T const & first() const {
    return this->first_;
  }

  /// \brief Returns the second value used in the ctor.
  T const & second() const {
    return this->second_;
  }

  /// \brief Returns the minimum value of the range.
  T minimum() const {
    return (this->first_ < this->second_) ? first_ : second_;
  }

  /// \brief Returns the maximum value of the range.
  T maximum() const {
    return (this->second_ > this->first_) ? this->second_ : this->first_;
  }

  /// \brief Returns second - first.
  /// \note If first > second, this will return a negative value,
  ///  which is perfectly acceptable.
  T getSpan() const {
    return (this->second_ - this->first_);
  }

private:
  /// \brief stores the first value provided in the ctor
  T first_;
  /// \brief stores the second value provided in the ctor
  T second_;
};

/// \brief returns a bool indicating whether a NamedType is
/// within a given ValueRange
template <typename T>
bool isInRange(NamedType<T> const & value, ValueRange<T> const & range) {
  if (value.get() < range.minimum())
    return false;
  if (value.get() > range.maximum())
    return false;

  else
    return true;
}

/// \brief returns a bool indicating whether a value is
/// within a given ValueRange
template <typename T>
bool isInRange(T const & value, ValueRange<T> const & range) {
  if (value < range.minimum())
    return false;
  if (value > range.maximum())
    return false;

  else
    return true;
}

/// \brief Returns a vector starting from ValueRange::first()
/// and ending at <= ValueRange::second().
///
/// The vector will start at ValueRange::first(),
/// will increment based on the value provided.
/// In any case of an error an empty vector will be returned.
template <typename T>
std::vector<T> slice(ValueRange<T> const & range, T increment) {
  // Error checking
  if (range.getSpan() > 0 && increment < 0)
    return std::vector<T>();
  if (range.getSpan() < 0 && increment > 0)
    return std::vector<T>();

  T nextVal = range.first();
  T const lastVal = range.second();

  if (nextVal < lastVal) {
    std::vector<T> slicedRange;

    while (nextVal <= lastVal) {
      slicedRange.push_back(nextVal);
      nextVal += increment;
    }
    return slicedRange;
  } else if (nextVal > lastVal) {
    std::vector<T> slicedRange;

    while (nextVal >= lastVal) {
      slicedRange.push_back(nextVal);
      nextVal += increment;
    }
    return slicedRange;
  } else // nextVal == lastVal
  {
    return std::vector<T>();
  }
}
} // namespace core
} // namespace nbt
