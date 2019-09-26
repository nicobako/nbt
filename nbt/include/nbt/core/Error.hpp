#pragma once

#include <string>
#include <typeinfo>

#include <nbt/core/ValueRange.hpp>

#include <fmt/format.h>

/// \file Error.hpp
/// \bried Generate Errors

namespace nbt {
namespace core {
/// \brief Generate an error of type \a Error_t.
///
/// \note This function constructs an \a Error_t object
/// using an Error_t(char*) constructor.
template <class Error_t, class Value_t>
Error_t make_error(
    std::string const & className,
    std::string const & variableName,
    Value_t const & value,
    nbt::core::ValueRange<Value_t> const & valueRange) {
  std::string errorMessage;
  errorMessage.append("ERROR: " + std::string(typeid(Error_t).name()) + "\n");
  errorMessage.append("class name: " + className + "\n");
  errorMessage.append("variable name: " + variableName + "\n");
  errorMessage.append(fmt::format(
      "acceptable values: [{0},{1}\n",
      valueRange.first(),
      valueRange.second()));

  return Error_t(errorMessage.c_str());
}

/// \brief generates a simple error message
template <class Error_t>
Error_t make_error(
    std::string const & mainMessage,
    std::string const & detailedMessage) {
  return Error_t(std::string(mainMessage + "\n" + detailedMessage).c_str());
}

/// \brief generates a simple error message
template <class Error_t> Error_t make_error(std::string const & message) {
  return Error_t((mainMessage).c_str());
}
} // namespace core
} // namespace nbt
