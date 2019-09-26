#include "BinaryTests.hpp"

#include <nbt/binary/FileReader.hpp>
#include <nbt/binary/FileWriter.hpp>

#include <catch2/catch.hpp>

TEST_CASE("nbt::binary tests", "[nbt_binary]") {

  std::string fileName = relativePath + "myNewBinFile.bin";

  std::unique_ptr<nbt::binary::FileWriter> bw;
  bw.reset(new nbt::binary::FileWriter(fileName));

  SECTION("initialization") {
    CHECK_THAT(bw->getFileName().c_str(), Catch::Equals(fileName.c_str()));

    CHECK(bw->isOpen() == true);
  }

  SECTION("close") {
    bw->close();

    CHECK(bw->isOpen() == false);
  }

  SECTION("writeInt") {
    int x = 5;

    bw->write(x);
  }

  SECTION("writeUint") {
    unsigned x = 10;

    bw->write(x);
  }

  SECTION("writeDouble") {
    double x = 0.50;

    bw->write(x);
  }

  SECTION("writeFloat") {
    float x = 0.50f;

    bw->write(x);
  }

  SECTION("shouldWriteString") {
    std::string aString = "A string";

    std::string file = "StringWriting.str";
    nbt::binary::FileWriter writer(file, false, nbt::binary::EndiannessLittle);

    writer.write(aString);

    writer.close();

    nbt::binary::FileReader reader(file, nbt::binary::EndiannessLittle);

    std::string readString = reader.get_next_n<std::string>(aString.size());

    CHECK_THAT(readString.c_str(), Catch::Equals(aString.c_str()));
  }

  SECTION("shouldWriteStringInReverseForBigEndian") {
    std::string aString = "A string";

    std::string file = relativePath + "StringWriting.str";
    nbt::binary::FileWriter writer(file, false, nbt::binary::EndiannessBig);

    writer.write(aString);

    writer.close();

    nbt::binary::FileReader reader(file, nbt::binary::EndiannessBig);

    std::string readString = reader.get_next_n<std::string>(aString.size());
    std::reverse(readString.begin(), readString.end());

    CHECK(readString == aString);
  }
}
