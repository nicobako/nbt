#include "ConfigTests.hpp"

#include <nbt/ascii/Conversions.hpp>
#include <nbt/config/Data.hpp>
#include <nbt/core/random.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Data tests", "[nbt_config]") {

  nbt::config::Data configData;

  std::string configFileName = "SampleConfigFile.txt";

  REQUIRE_NOTHROW(
      configData = nbt::config::parse_file(relativePath + configFileName));

  REQUIRE(!configData.empty());

  SECTION("shouldIndicateIfItIsEmpty") {
    nbt::config::Data emptyConfigData;
    CHECK(emptyConfigData.empty());

    auto bogusFileName = nbt::core::random<std::string>();
    auto bogusConfigData = nbt::config::parse_file(bogusFileName);
    CHECK(bogusConfigData.empty());

    REQUIRE(!configData.empty());
  }

  SECTION("shouldIndicateWhetherCertainPropertiesWereFoundInFile") {
    CHECK(configData.has("bogus_section", "bogus_property") == false);

    CHECK(configData.has("section_0", "property_0") == true);
    CHECK(configData.has("section_0", "property_1") == true);

    CHECK(configData.has("section_1", "property_0") == true);
    CHECK(configData.has("section_1", "property_1") == true);
  }

  SECTION("propertiesInFileBeforeAnySectionShouldBeInGlobalSection") {
    CHECK(configData.has("global", "version") == true);
  }

  SECTION("shouldBeAbleToGetPropertyValues") {
    CHECK_THAT(
        configData.section("global").property("version").value().c_str(),
        Catch::Equals("1.0.0"));

    CHECK_THAT(
        configData.section("section_0").property("property_0").value().c_str(),
        Catch::Equals("0"));
    CHECK_THAT(
        configData.section("section_0").property("property_1").value().c_str(),
        Catch::Equals("1"));

    CHECK_THAT(
        configData.section("section_1").property("property_0").value().c_str(),
        Catch::Equals("Hello"));
    CHECK_THAT(
        configData.section("section_1").property("property_1").value().c_str(),
        Catch::Equals("World"));
  }

  SECTION("shouldReturnNullSectioneIfNotInFile") {
    // returning the default value
    CHECK(nbt::config::null_section == configData.section("bogus_section"));
  }

  SECTION("shouldReturnNullPropertyeIfNotInFile") {
    // returning the default value
    CHECK(
        nbt::config::null_property
        == configData.section("bogus_section").property("bogus_property"));
  }

  SECTION("shouldBeAbleToAccessListOfAllSections") {
    auto const & sections = configData.sections();

    REQUIRE(sections.size() > static_cast<unsigned>(6));

    std::for_each(
        sections.begin(),
        sections.end(),
        [&configData](nbt::config::Section const & s) {
          CHECK(configData.has(s.name()));
        });
  }

  SECTION("shouldStoreSectionPropertyValueWithSpaces") {
    auto value_with_spaces = configData.section("section with spaces")
                                 .property("property with spaces")
                                 .value();

    CHECK_THAT(value_with_spaces.c_str(), Catch::Equals("value with spaces"));
  }

  SECTION(
      "shouldBeAbleToReadSectionsPropertiesAndValuesWithNumbersAtBeginning") {
    CHECK_THAT(
        configData.section("1_section_with_num_at_beginning")
            .property("1_property_with_num_at_beginning")
            .value()
            .c_str(),
        Catch::Equals("1_value_with_num_at_beginning"));
  }

  SECTION("shouldBeAbleToAddSections") {
    nbt::config::Data cData;
    std::string section = "section";
    std::string property = "property";
    std::string value = "value";

    CHECK(cData.add(section));

    CHECK(cData.has(section));
  }

  SECTION("shouldReturnFalseIfAddingSectionAlreadyInData") {
    REQUIRE(configData.has("section_0"));
    CHECK(!configData.add("section_0"));
  }

  SECTION("shouldReturnFalseIfAddingPropertyAlreadyInData") {
    REQUIRE(configData.has("section_0", "property_0"));

    auto oldProp = configData.section("section_0").property("property_0");

    CHECK(!configData.add("section_0", "property_0", "new value"));

    auto newProp = configData.section("section_0").property("property_0");

    CHECK_THAT("new value", Catch::Equals(newProp.value().c_str()));
    CHECK(newProp == oldProp);
  }

  SECTION("shouldReturnRequestedSection") {
    auto globalSection = configData.section("global");

    CHECK_THAT(globalSection.name().c_str(), Catch::Equals("global"));
    CHECK(globalSection.has("version"));
  }

  SECTION("shouldBeAbleToRemoveSection") {
    // make sure the section exists
    REQUIRE(configData.has("section_0"));

    // since we know it exists removing it should return true
    CHECK(configData.remove("section_0"));

    // the section should no longer exist
    CHECK(!configData.has("section_0"));

    // subsequent calls to remove the section should return true
    CHECK(!configData.remove("section_0"));
  }

  SECTION("shouldBeAbleToRemovePropertyFromSection") {
    REQUIRE(configData.has("section_0", "property_0"));

    CHECK(configData.remove("section_0", "property_0"));

    CHECK(!configData.has("section_0", "property_0"));

    CHECK(!configData.remove("section_0", "property_0"));
  }
}
