#include "AsciiTests.hpp"

#include <algorithm> //std::transform
#include <iterator>  // std::back_inserter
#include <string>

#include <nbt/ascii/Conversions.hpp>
#include <nbt/ascii/Regex.hpp>
#include <nbt/core/random.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Regex tests", "[nbt_ascii]") {

  std::string line = "A line with tokens";
  std::string lineWithNumbers = "1, 1.0, 2.404";

  SECTION("shouldTokenizeLine") {
    auto tokens = nbt::ascii::split(line);

    CHECK_THAT(tokens.at(0).c_str(), Catch::Equals("A"));
    CHECK_THAT(tokens.at(1).c_str(), Catch::Equals("line"));
    CHECK_THAT(tokens.at(2).c_str(), Catch::Equals("with"));
    CHECK_THAT(tokens.at(3).c_str(), Catch::Equals("tokens"));
  }

  SECTION("shouldNotTokenizePeriodsOrDecimalsByDefault") {
    auto tokens = nbt::ascii::split(lineWithNumbers);

    CHECK_THAT(tokens.at(0).c_str(), Catch::Equals("1"));
    CHECK_THAT(tokens.at(1).c_str(), Catch::Equals("1.0"));
    CHECK_THAT(tokens.at(2).c_str(), Catch::Equals("2.404"));
  }

  SECTION("shouldBeAbleToconvertTokensToOtherBuiltInTypes") {
    auto tokens = nbt::ascii::split(lineWithNumbers);

    std::vector<float> tokens_vec;

    std::transform(
        tokens.begin(),
        tokens.end(),
        std::back_inserter(tokens_vec),
        nbt::ascii::convert_to<float, std::string>);

    REQUIRE(tokens_vec.size() == 3);

    CHECK(tokens_vec.at(0) == Approx(1.0f));
    CHECK(tokens_vec.at(1) == Approx(1.0f));
    CHECK(tokens_vec.at(2) == Approx(2.404f));
  }

  SECTION("shouldBeAbleToSearchLine") {
    std::string line = "Name = value #and other stuff that would"
                       "cause this search to fail if it were a match...";

    // using regex
    auto regex_search_results = nbt::ascii::search(line, "(\\w*)[\\s=]+(\\w*)");
    REQUIRE(regex_search_results.size() == 3);
    CHECK_THAT(
        regex_search_results.at(0).c_str(), Catch::Equals("Name = value"));
    CHECK_THAT(regex_search_results.at(1).c_str(), Catch::Equals("Name"));
    CHECK_THAT(regex_search_results.at(2).c_str(), Catch::Equals("value"));

    // using plain ascii search
    auto ascii_search_results = nbt::ascii::search(line, "Name = value");
    REQUIRE(ascii_search_results.size() == 1);
    CHECK_THAT(
        ascii_search_results.at(0).c_str(), Catch::Equals("Name = value"));

    // using combo ascii and regex search
    auto combo_search_results = nbt::ascii::search(line, "Name = (\\w+)");
    REQUIRE(combo_search_results.size() == 2);
    CHECK_THAT(
        combo_search_results.at(0).c_str(), Catch::Equals("Name = value"));
    CHECK_THAT(combo_search_results.at(1).c_str(), Catch::Equals("value"));
  }

  SECTION("shouldBeAbleToMatchLine") {
    std::string valid_line = "keyword = value";
    std::string invalid_line = " keyword = value # has space in front";

    // using regex
    std::string match_re = "(\\w+)[\\s=]+(\\w+)";

    auto match_results_regex_valid = nbt::ascii::match(valid_line, match_re);
    auto match_regex_invalid = nbt::ascii::match(invalid_line, match_re);

    REQUIRE(match_results_regex_valid.size() == 3);
    CHECK_THAT(
        match_results_regex_valid[0].c_str(), Catch::Equals("keyword = value"));
    CHECK_THAT(match_results_regex_valid[1].c_str(), Catch::Equals("keyword"));
    CHECK_THAT(match_results_regex_valid[2].c_str(), Catch::Equals("value"));

    CHECK(match_regex_invalid.empty() == true);

    // using plain ascii match
    std::string match_ascii = "keyword = value";

    auto match_results_ascii_valid = nbt::ascii::match(valid_line, match_ascii);
    auto match_results_ascii_invalid =
        nbt::ascii::match(invalid_line, match_ascii);

    REQUIRE(match_results_ascii_valid.size() == 1);
    CHECK_THAT(
        match_results_ascii_valid.at(0).c_str(),
        Catch::Equals("keyword = value"));

    CHECK(match_results_ascii_invalid.empty() == true);

    // using combo ascii and regex match
    std::string match_combo = "keyword = (.+)";

    auto match_results_combo_valid = nbt::ascii::match(valid_line, match_combo);

    auto match_results_combo_invalid =
        nbt::ascii::match(invalid_line, match_combo);

    REQUIRE(match_results_combo_valid.size() == 2);
    CHECK_THAT(
        match_results_combo_valid.at(0).c_str(),
        Catch::Equals("keyword = value"));
    CHECK_THAT(match_results_combo_valid.at(1).c_str(), Catch::Equals("value"));

    CHECK(match_results_combo_invalid.empty() == true);
  }

  SECTION("shouldBeAbleToFindAllMatchesInLine") {
    std::string line = "0, 1, 2, 3";

    auto all_num_pairs = nbt::ascii::find_all(line, "(\\d+).*?(\\d+)");

    REQUIRE(all_num_pairs.size() == 2);

    CHECK_THAT(all_num_pairs.at(0).at(0).c_str(), Catch::Equals("0, 1"));
    CHECK_THAT(all_num_pairs.at(0).at(1).c_str(), Catch::Equals("0"));
    CHECK_THAT(all_num_pairs.at(0).at(2).c_str(), Catch::Equals("1"));

    CHECK_THAT(all_num_pairs.at(1).at(0).c_str(), Catch::Equals("2, 3"));
    CHECK_THAT(all_num_pairs.at(1).at(1).c_str(), Catch::Equals("2"));
    CHECK_THAT(all_num_pairs.at(1).at(2).c_str(), Catch::Equals("3"));

    std::string line_1 = "one pair, two pair";

    auto all_word_pairs = nbt::ascii::find_all(line_1, "(\\w+\\s\\w+)");

    REQUIRE(all_word_pairs.size() == 2);

    CHECK_THAT(all_word_pairs.at(0).at(0).c_str(), Catch::Equals("one pair"));
    CHECK_THAT(all_word_pairs.at(1).at(0).c_str(), Catch::Equals("two pair"));
  }

  SECTION("shouldBeAbleToReplaceMatchesInLine") {
    std::string line = "I am a line, aren't I?";

    std::string replaced_results;

    // test 1 - capturing a group
    replaced_results = nbt::ascii::replace(line, "([aeiouAEIOU])", "-$1-");

    CHECK_THAT(
        replaced_results.c_str(),
        Catch::Equals("-I- -a-m -a- l-i-n-e-, -a-r-e-n't -I-?"));

    // test 2 - not capturing a group
    replaced_results = nbt::ascii::replace(line, "\\?", "!");

    CHECK_THAT(
        replaced_results.c_str(), Catch::Equals("I am a line, aren't I!"));

    replaced_results = nbt::ascii::replace(line, "a line,", "many lines,\n");

    CHECK_THAT(
        replaced_results.c_str(),
        Catch::Equals("I am many lines,\n aren't I?"));
  }

  SECTION("shouldBeAbleToTrimLine") {
    std::string lineWithSpaces = "  some stuff ...   ";

    nbt::ascii::trim(lineWithSpaces, " ");

    CHECK_THAT(lineWithSpaces.c_str(), Catch::Equals("some stuff ..."));
  }

  SECTION("shouldNotTrimAnSfromLineWhenWantingToTrimSpaces") {
    std::string lineWithS = "speeds";
    nbt::ascii::trim(lineWithS, "\\s");

    CHECK_THAT(lineWithS.c_str(), Catch::Equals("speeds"));
  }

  SECTION("shouldNotCrashWhenTrimmingEmptyLine") {
    std::string emptyLine = "";
    nbt::ascii::trim(emptyLine, nbt::core::random<std::string>());

    CHECK_THAT(emptyLine.c_str(), Catch::Equals(""));
  }

  SECTION("shouldNotCrashWhenTrimmingLineWithOnlySpaces") {
    std::string spaces = "    ";
    nbt::ascii::trim(spaces, " ");

    CHECK_THAT(spaces.c_str(), Catch::Equals(""));
  }

  SECTION("shouldTrimMultipleCharactersFromLine") {
    std::string line = " _ @$ hello _$$@ ";
    nbt::ascii::trim(line, " @$_");
    CHECK_THAT(line.c_str(), Catch::Equals("hello"));

    std::string lineWithOnlyChars = "_##";
    nbt::ascii::trim(lineWithOnlyChars, "_##");
    CHECK_THAT(lineWithOnlyChars.c_str(), Catch::Equals(""));
  }

  SECTION("shouldBeAbleToJoinContainerOfStrings") {
    std::vector<std::string> strings;
    strings.push_back("hello");
    strings.push_back("there!");

    auto joint_str = nbt::ascii::join(strings.begin(), strings.end(), " ");

    CHECK_THAT(joint_str.c_str(), Catch::Equals("hello there!"));
  }
}