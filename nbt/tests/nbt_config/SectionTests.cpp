
#include "ConfigTests.hpp"

#include <fstream>
#include <nbt/ascii/Conversions.hpp>
#include <nbt/config/Section.hpp>
#include <nbt/core/random.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Section tests", "[nbt_config]") {
  SECTION("shouldHaveName") {
    auto name = nbt::core::random<std::string>();

    nbt::config::Section s(name);

    CHECK_THAT(s.name().c_str(), Catch::Equals(name.c_str()));
  }

  SECTION("shouldIndicateIfItIsEmpty") {
    nbt::config::Section s("empty_section");

    CHECK(s.empty());
  }
  SECTION("shouldHaveProperties") {
    auto make_random_prop = []() -> nbt::config::Property {
      auto pName = nbt::core::random<std::string>();
      auto pValue = nbt::core::random<std::string>();
      nbt::config::Property p(pName, pValue);
      return p;
    };

    auto make_random_section = []() -> nbt::config::Section {
      auto sName = nbt::core::random<std::string>();
      nbt::config::Section s(sName);
      return s;
    };

    auto p1 = make_random_prop();
    auto p2 = make_random_prop();
    auto s = make_random_section();
    CHECK(s.has(p1) == false);
    CHECK(s.has(p2) == false);
    CHECK(s.has(p1.name()) == false);
    CHECK(s.has(p2.name()) == false);
    s.add(p1);
    s.add(p2);
    CHECK(s.has(p1) == true);
    CHECK(s.has(p2) == true);
    CHECK(s.has(p1.name()) == true);
    CHECK(s.has(p2.name()) == true);
  }

  SECTION("shouldNotAddPropertyIfAlreadyIsInSection") {
    auto make_random_prop = []() -> nbt::config::Property {
      auto pName = nbt::core::random<std::string>();
      auto pValue = nbt::core::random<std::string>();
      nbt::config::Property p(pName, pValue);
      return p;
    };

    auto make_random_section = []() -> nbt::config::Section {
      auto sName = nbt::core::random<std::string>();
      nbt::config::Section s(sName);
      return s;
    };

    auto p1 = make_random_prop();
    // p2 has same name as p1, but different value
    auto p2 =
        nbt::config::Property(p1.name(), nbt::core::random<std::string>());

    auto s = make_random_section();
    CHECK(s.has(p1) == false);
    CHECK(s.has(p2) == false);

    CHECK(s.add(p1) == true);
    CHECK(s.add(p2) == false);

    CHECK(s.has(p1) == true);
    CHECK(s.has(p2) == true);
  }

  SECTION("shouldReturnPropertyWithNameRequested") {
    auto make_random_prop = []() -> nbt::config::Property {
      auto pName = nbt::core::random<std::string>();
      auto pValue = nbt::core::random<std::string>();
      nbt::config::Property p(pName, pValue);
      return p;
    };

    auto make_random_section = []() -> nbt::config::Section {
      auto sName = nbt::core::random<std::string>();
      nbt::config::Section s(sName);
      return s;
    };

    auto p1 = make_random_prop();

    auto s = make_random_section();
    CHECK(s.has(p1) == false);
    CHECK(s.add(p1) == true);
    CHECK(s.has(p1) == true);
  }

  SECTION("shouldReturnPropertyWithDefaultValueIfItDoesntExist") {
    auto make_random_section = []() -> nbt::config::Section {
      auto sName = nbt::core::random<std::string>();
      nbt::config::Section s(sName);
      return s;
    };

    auto s = make_random_section();

    CHECK(s.property("dummy prop") == nbt::config::null_property);
  }

  SECTION("shouldBeAbleToRemoveProperties") {
    auto make_random_prop = []() -> nbt::config::Property {
      auto pName = nbt::core::random<std::string>();
      auto pValue = nbt::core::random<std::string>();
      nbt::config::Property p(pName, pValue);
      return p;
    };

    auto make_random_section = []() -> nbt::config::Section {
      auto sName = nbt::core::random<std::string>();
      nbt::config::Section s(sName);
      return s;
    };

    auto s = make_random_section();

    auto p1 = make_random_prop();

    // since it is not in the section yet, should be false
    CHECK(s.remove(p1) == false);
    CHECK(s.add(p1) == true);
    CHECK(s.has(p1) == true);
    CHECK(s.remove(p1) == true);
    CHECK(s.has(p1) == false);

    // since it is not in the section yet, should be false
    CHECK(s.remove(p1.name()) == false);
    CHECK(s.add(p1) == true);
    CHECK(s.has(p1.name()) == true);
    CHECK(s.remove(p1.name()) == true);
    CHECK(s.has(p1.name()) == false);
  }

  SECTION("shouldBeAbleToReplaceProperties") {
    auto make_random_prop = []() -> nbt::config::Property {
      auto pName = nbt::core::random<std::string>();
      auto pValue = nbt::core::random<std::string>();
      nbt::config::Property p(pName, pValue);
      return p;
    };

    auto make_random_section = []() -> nbt::config::Section {
      auto sName = nbt::core::random<std::string>();
      nbt::config::Section s(sName);
      return s;
    };

    auto s = make_random_section();
    auto p1 = make_random_prop();
    // same name as p1, but different value
    auto p2 =
        nbt::config::Property(p1.name(), nbt::core::random<std::string>());
    // different name as p1, but same value
    auto p3 =
        nbt::config::Property(nbt::core::random<std::string>(), p1.value());

    s.add(p1);
    CHECK_THAT(
        s.property(p1.name()).value().c_str(),
        Catch::Equals(p1.value().c_str()));
    CHECK(s.replace(p2) == true);
    CHECK_THAT(
        s.property(p2.name()).value().c_str(),
        Catch::Equals(p2.value().c_str()));
    CHECK_THAT(
        s.property(p2.name()).value().c_str(),
        Catch::Equals(p2.value().c_str()));

    CHECK(s.replace(p3) == false);
    CHECK(s.has(p3) == false);
  }

  SECTION("shouldReturnListOfAllPropertyNames") {
    auto make_random_prop = []() -> nbt::config::Property {
      auto pName = nbt::core::random<std::string>();
      auto pValue = nbt::core::random<std::string>();
      nbt::config::Property p(pName, pValue);
      return p;
    };

    auto make_random_section = []() -> nbt::config::Section {
      auto sName = nbt::core::random<std::string>();
      nbt::config::Section s(sName);
      return s;
    };

    auto s = make_random_section();

    auto p1 = nbt::config::Property("p1", "1");
    auto p2 = nbt::config::Property("p2", "2");

    s.add(p1);
    s.add(p2);

    auto props = s.properties();

    REQUIRE(props.size() > 1);
    CHECK_THAT(props.find(p1)->name().c_str(), Catch::Equals("p1"));
    CHECK_THAT(props.find(p2)->name().c_str(), Catch::Equals("p2"));
  }
}
