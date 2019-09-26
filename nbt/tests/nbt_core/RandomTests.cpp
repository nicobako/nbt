#include <nbt/core/NamedType.hpp>
#include <nbt/core/ValueRange.hpp>
#include <nbt/core/random.hpp>

#include <catch2/catch.hpp>

class Age : public nbt::core::NamedType<int> {
public:
  Age(int age) : nbt::core::NamedType<int>(age) {}

  bool isSenior() {
    return this->get() >= 65;
  }
  bool isMinor() {
    return this->get() < 18;
  }
};

TEST_CASE("Random tests", "[nbt_core]") {
  SECTION("shouldGenerateRandomNamedType") {
    // nbt::core::NamedType<int> val(nbt::core::random<int>());

    CHECK_NOTHROW(nbt::core::random<int>());
  }

  SECTION("shouldGenerateRandomNamedTypeInRange") {
    nbt::core::ValueRange<int> range(0, 10);
    for (int i = 0; i < 100; i++) {
      nbt::core::NamedType<int> val(nbt::core::random(range));
      CHECK(nbt::core::isInRange(val, range) == true);
    }

    nbt::core::ValueRange<float> rf(0.0f, 1.0f);
    for (int i = 0; i < 100; i++) {
      nbt::core::NamedType<float> vf(nbt::core::random(rf));
      CHECK(nbt::core::isInRange(vf, rf) == true);
    }
  }

  SECTION("shouldBeAbleToGenerateClassDerivedFromNbtVoAny") {
    Age age(nbt::core::random<int>());
  }

  SECTION("shouldBeAbleToGenerateString") {
    std::string str = nbt::core::random<std::string>();

    CHECK(0 < static_cast<int>(str.size()));
  }
}
