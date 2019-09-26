#pragma once

#include <iostream>

namespace nbt {
namespace core {
/// \brief Class that represents a *strong type*
///
/// \todo Perhaps remove template parameter \p P???
///
/// For more information on strong types see Jonathan Boccara's
/// blog
/// https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/,
template <typename T, typename P = struct NamedTypeParameter> class NamedType {
public:
  NamedType(T const & value) : value_(value) {}

  NamedType(T && value) : value_(value) {}

  virtual ~NamedType() {}

  /// \brief A NamedType object cannot be assigned
  ///  a different value once instantiated.
  /// \note These are declared but not defined.
  ///  Using these will lead to compilation error.
  NamedType<T> & operator=(T const & rhs);
  /// \brief A NamedType object cannot be assigned
  ///  a different value once instantiated.
  /// \note These are declared but not defined.
  ///  Using these will lead to compilation error.
  NamedType<T> & operator=(NamedType<T> const & rhs);

  /// \brief stores the type of the value
  typedef T type;

  /// \brief Returns the value
  T const & get() const {
    return this->value_;
  }

  /// \brief logical operators
  bool operator==(NamedType<T> const & rhs) const {
    return this->get() == rhs.get();
  }

  /// \brief logical operators
  bool operator!=(NamedType<T> const & rhs) const {
    return !(*this == rhs);
  }

private:
  /// \brief The value itself
  T value_;
};

} // namespace core
} // namespace nbt
