#include <nbt/core/math.hpp>

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include <catch2/catch.hpp>

TEST_CASE("MathTests: shouldCreatePerpendicularVector", "[nbt_core]") {
  glm::vec3 anyVec(1.0f, 0.0f, 0.0f);

  glm::vec3 vPerpendicular = nbt::core::createPerpendicularVec3(anyVec);

  // The dot product of two perpendicular vectors is 0

  float dotProduct = glm::dot(anyVec, vPerpendicular);

  CHECK(dotProduct == 0.0f);
}

TEST_CASE("MathTests: shouldBeAbleToGenerateNan", "[nbt_core]") {
  // here we demonstrate how to create nan using std::
  auto nan = std::numeric_limits<double>::quiet_NaN();
  // and how to test for nan
  CHECK(!(nan == nan));

  auto nan_test = nbt::core::nan<double>();
  CHECK(!(nan_test == nan_test));
}

TEST_CASE("MathTests: shouldBeAbleToTestIfValueIsNan", "[nbt_core]") {
  // here we demonstrate how to create nan using std::
  auto nan = std::numeric_limits<double>::quiet_NaN();
  // and how to test for nan
  CHECK(!(nan == nan));

  CHECK(nbt::core::is_nan(nan));
}