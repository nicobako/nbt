#include "AsciiTests.hpp"

#include <nbt/ascii/Conversions.hpp>
#include <nbt/ascii/Regex.hpp>
#include <nbt/core/random.hpp>

#include <glm/vec3.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Conversions tests", "[nbt_ascii]") {

  int anyInt = nbt::core::random<int>();

  SECTION("shouldConvertStringToInt") {
    int zero_int = nbt::ascii::convert_to<int>("0");
    int one_int = nbt::ascii::convert_to<int>("1");

    CHECK(zero_int == 0);
    CHECK(one_int == 1);
  }

  SECTION("shouldConvertIntToString") {
    int one_int = 1;
    std::string one_string = nbt::ascii::convert_to<std::string>(one_int);
    CHECK_THAT(one_string.c_str(), Catch::Equals("1"));

    int bigNum_int = 123456;
    std::string bigNumString = nbt::ascii::convert_to<std::string>(bigNum_int);
    CHECK_THAT(bigNumString.c_str(), Catch::Equals("123456"));
  }

  SECTION("shouldConvertStringToFloat") {
    std::string float_string = "1234.5678";
    float float_float = nbt::ascii::convert_to<float>(float_string);
    CHECK(float_float == 1234.5678f);
  }

  SECTION("shouldConvertFloatsToString") {
    float float_float = 123.456f;
    std::string float_string = nbt::ascii::convert_to<std::string>(float_float);
    CHECK_THAT(float_string.c_str(), Catch::Equals("123.456"));
  }

  SECTION("shouldBeAbleToMakeUpperCaseString") {
    std::string token("lower_case");
    auto str_upper = nbt::ascii::to_upper(token);
    CHECK_THAT(str_upper.c_str(), Catch::Equals("LOWER_CASE"));
  }

  SECTION("shouldBeAbleToMakeLowerCaseString") {
    std::string token("UPPER_CASE");
    auto str_lower = nbt::ascii::to_lower(token);
    CHECK_THAT(str_lower.c_str(), Catch::Equals("upper_case"));
  }

  SECTION("shouldBeAbleToConvertContainerOfTypes") {
    auto csv_str = nbt::ascii::split("1.1, 2.2, 3.3");

    auto csv_values = nbt::ascii::convert_all_to<std::vector<double>>(csv_str);

    REQUIRE(csv_values.size() == 3);

    CHECK(csv_values.at(0) == 1.1);
    CHECK(csv_values.at(1) == 2.2);
    CHECK(csv_values.at(2) == 3.3);

    auto csv_values_str =
        nbt::ascii::convert_all_to<std::vector<std::string>>(csv_values);

    REQUIRE(csv_values_str.size() == 3);

    CHECK_THAT(csv_values_str.at(0).c_str(), Catch::Equals("1.1"));
    CHECK_THAT(csv_values_str.at(1).c_str(), Catch::Equals("2.2"));
    CHECK_THAT(csv_values_str.at(2).c_str(), Catch::Equals("3.3"));
  }

  SECTION("shouldBeAbleToTellIfCanConvert") {
    CHECK(nbt::ascii::can_convert_to<int>("0"));

    CHECK(!nbt::ascii::can_convert_to<int>("not a number"));
  }

  SECTION("shouldBeAbleToConvertGlmVecTypes") {
    glm::vec3 v3(1.0f, 2.0f, 3.0f);

    std::string v3_str("(1.0, 2.0, 3.0)");

    CHECK(nbt::ascii::convert_to_vec<glm::vec3>(v3_str) == v3);
  }

  SECTION("shouldBeAbleToTellIfCanConvertToGlmVecTypes") {
    std::string invalid_v3_str = "a, b, c";
    CHECK(!nbt::ascii::can_convert_to_vec<glm::vec3>(invalid_v3_str));

    std::string valid_v3_str = "1, 2, 3";
    CHECK(nbt::ascii::can_convert_to_vec<glm::vec3>(valid_v3_str));
  }
}