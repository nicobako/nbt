#include "ConfigTests.hpp"

#include <nbt/config/Property.hpp>
#include <nbt/core/random.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Property tests", "[nbt_config]") {

  SECTION("shouldHaveNameAndValue") {
    std::string name = nbt::core::random<std::string>();
    std::string value = nbt::core::random<std::string>();

    nbt::config::Property p(name, value);

    CHECK_THAT(p.name().c_str(), Catch::Equals(name.c_str()));
    CHECK_THAT(p.value().c_str(), Catch::Equals(value.c_str()));
  }

  SECTION("shouldBeAbleToCompareEqualityOfTwoProperties") {
    nbt::config::Property p_1_1("1", "1");
    nbt::config::Property p_1_2("1", "2");
    nbt::config::Property p_1_1_also("1", "1");

    CHECK(p_1_1 == p_1_1_also);
    CHECK(!(p_1_1 == p_1_2));
  }
}
