#include <nbt/core/Error.hpp>
#include <nbt/core/ValueRange.hpp>
#include <nbt/core/random.hpp>

#include <fmt/format.h>

#include <catch2/catch.hpp>

TEST_CASE("Error tests", "[nbt_core]") {

  std::string className = nbt::core::random<std::string>();
  std::string variableName = nbt::core::random<std::string>();
  int value = nbt::core::random<int>();

  std::unique_ptr<nbt::core::ValueRange<int>> valueRange(
      new nbt::core::ValueRange<int>(0, 10));

  SECTION("shouldGenerateErrorWithAppropriateString") {
    auto error = nbt::core::make_error<std::string>(
        className, variableName, value, *valueRange);

    std::cout << error;

    std::string expectedErrorMessage;
    expectedErrorMessage.append(
        "ERROR: class std::basic_string<char,struct "
        "std::char_traits<char>,class std::allocator<char> >\n");
    expectedErrorMessage.append("class name: " + className + "\n");
    expectedErrorMessage.append("variable name: " + variableName + "\n");
    expectedErrorMessage.append(fmt::format(
        "acceptable values: [{0},{1}\n",
        valueRange->first(),
        valueRange->second()));

    CHECK_THAT(error.c_str(), Catch::Equals(expectedErrorMessage.c_str()));
  }
}