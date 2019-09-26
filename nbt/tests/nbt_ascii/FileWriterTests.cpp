#include "AsciiTests.hpp"

#include <memory>

#include <nbt/ascii/FileWriter.hpp>

#include <catch2/catch.hpp>

TEST_CASE("FileWriter tests", "[nbt_ascii]") {

  std::string fileName;
  std::unique_ptr<nbt::ascii::FileWriter> fw;

  fileName = "NewFile.txt";
  fw.reset(new nbt::ascii::FileWriter(fileName, true));

  SECTION("shouldBeInitializedWithFileNameAndBoolToAppendToFile") {
    CHECK_THAT(fw->getFileName(), Catch::Equals(fileName));

    CHECK(fw->isOpen() == true);
  }

  SECTION("close") {
    CHECK(fw->isOpen() == true);

    fw->close();

    CHECK(fw->isOpen() == false);
  }

  SECTION("writeString") {
    std::string text("Hello world string");
    fw->write(text, true);
  }

  SECTION("writeCharConstPtr") {
    fw->write("Hello world char const *", true);
  }

  SECTION("writeInt") {
    fw->write("int ", false);
    int x = 0;
    fw->write(x, true);
  }

  SECTION("writeUnsigned") {
    fw->write("unsigned ", false);
    unsigned x = 1;
    fw->write(x, true);
  }

  SECTION("writeFloat") {
    fw->write("float ", false);
    float x = 2.2222222f;
    fw->write(x, true);
  }

  SECTION("writeDouble") {
    fw->write("double ", false);
    double x = 3.3333333333;
    fw->write(x, true);
  }

  SECTION("writeBool") {
    fw->write("bool ", false);
    bool x = true;
    fw->write(x, true);
  }
}