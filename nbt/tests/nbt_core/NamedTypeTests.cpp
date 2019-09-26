#include <nbt/core/NamedType.hpp>

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

TEST_CASE("NamedType tests", "[nbt_core]") {
  SECTION("shouldBeEqualToInitializedNamedType") {
    // Checking for ints
    nbt::core::NamedType<int> val(0);
    CHECK(val.get() == 0);

    // checking for strings
    std::string name("Bob");
    nbt::core::NamedType<std::string> valName(name);
    CHECK_THAT(valName.get().c_str(), Catch::Equals(name.c_str()));
  }

  SECTION("shouldBeAbleToTellIfTwoNamedTypesAreEqual") {
    nbt::core::NamedType<int> val(0);
    nbt::core::NamedType<int> val0(0);
    nbt::core::NamedType<int> val1(1);

    CHECK((val == val0) == true);
    CHECK((val == val1) == false);
  }

  SECTION("shouldBeAbleToTellIfTwoNamedTypesAreNOTEqual") {
    nbt::core::NamedType<int> val(0);
    nbt::core::NamedType<int> val0(0);
    nbt::core::NamedType<int> val1(1);

    CHECK((val != val0) == false);
    CHECK((val != val1) == true);
  }

  SECTION("shouldHaveCopyConstructor") {
    nbt::core::NamedType<int> nt = 5;
    CHECK(5 == nt.get());
  }
  SECTION("shouldNotBeAbleToAlterANamedTypeOnceInstantiated") {
    nbt::core::NamedType<float> val5(5.0f);
    nbt::core::NamedType<float> val10(10.0f);

    // val5 = val10; // will not compile... YAY!!!
  }

  SECTION("derivingFromNbtVoNamedTypeShouldBeEasy") {
    Age age100(100);

    CHECK(age100.isMinor() == false);
    CHECK(age100.isSenior() == true);
  }
}
