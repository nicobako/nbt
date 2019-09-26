#include "AsciiTests.hpp"

#include <memory>

#include <nbt/ascii/FileReader.hpp>

#include <catch2/catch.hpp>

TEST_CASE("FileReader tests", "[nbt_ascii]") {

  std::string validFileName, invalidFileName;

  std::unique_ptr<nbt::ascii::FileReader> validFr;
  std::unique_ptr<nbt::ascii::FileReader> invalidFr;

  std::vector<std::string> lines;

  validFileName = relativePath + "FileSampleDoc.txt";

  validFr.reset(new nbt::ascii::FileReader(validFileName));

  invalidFileName = "InvalidFileName.txt";

  invalidFr.reset(new nbt::ascii::FileReader(invalidFileName));

  lines.push_back("This is merely a text file containing random stuff.");
  lines.push_back("");
  lines.push_back("Point");
  lines.push_back("0.0, 1.0, 2.0");
  lines.push_back("");
  lines.push_back("Another point");
  lines.push_back("3.0, 4.0, 5.0");

  SECTION("initialization") {
    CHECK(validFr->isOpen() == true);
    CHECK(invalidFr->isOpen() == false);

    CHECK(validFr->endOfFileReached() == false);
    CHECK(invalidFr->endOfFileReached() == true);

    CHECK(validFr->getCurrentLineNumber() == 0);
    CHECK(invalidFr->getCurrentLineNumber() == 0);

    CHECK_THAT(validFr->getCurrentLine().c_str(), Catch::Equals(""));
    CHECK_THAT(invalidFr->getCurrentLine().c_str(), Catch::Equals(""));

    CHECK_THAT(validFr->getPreviousLine().c_str(), Catch::Equals(""));
    CHECK_THAT(invalidFr->getPreviousLine().c_str(), Catch::Equals(""));
  }

  SECTION("getFileName") {
    CHECK_THAT(
        validFr->getFileName().c_str(), Catch::Equals(validFileName.c_str()));
    CHECK_THAT(
        invalidFr->getFileName().c_str(),
        Catch::Equals(invalidFileName.c_str()));
  }

  SECTION("getNextLineValidAsciiReader") {
    // Calling getNextLine on an valid and open nbt::ascii::FileReader object

    REQUIRE(validFr->isOpen() == true);

    std::string line = validFr->getNextLine();

    while (!validFr->endOfFileReached()) {
      unsigned curLineNum = validFr->getCurrentLineNumber();

      CHECK_THAT(line.c_str(), Catch::Equals(lines[curLineNum - 1].c_str()));

      line = validFr->getNextLine();
    }
  }

  SECTION("getNextLineInvalidAsciiReader") {
    // Calling getNextLine on an valid and open nbt::ascii::FileReader object

    std::string invalidLine = invalidFr->getNextLine();

    CHECK_THAT(invalidLine.c_str(), Catch::Equals(""));
  }

  SECTION("getCurrentLineNumber") {
    unsigned curLineNum = 0;
    while (!validFr->endOfFileReached()) {
      CHECK(validFr->getCurrentLineNumber() == curLineNum);

      validFr->getNextLine();

      curLineNum++;
    }
  }

  SECTION("close") {
    CHECK(invalidFr->isOpen() == false);

    invalidFr->close();
    CHECK(invalidFr->isOpen() == false);

    invalidFr->close();
    CHECK(invalidFr->isOpen() == false);

    CHECK(validFr->isOpen() == true);
    validFr->close();
    CHECK(validFr->isOpen() == false);
  }

  SECTION("callingCloseThenGetNextLine") {

    validFr->close();

    CHECK_THAT(validFr->getNextLine().c_str(), Catch::Equals(""));
  }
}