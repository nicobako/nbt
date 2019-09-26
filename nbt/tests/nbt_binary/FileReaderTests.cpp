#include "BinaryTests.hpp"

#include <nbt/binary/FileReader.hpp>

#include <catch2/catch.hpp>

TEST_CASE("FileReader tests", "[nbt_binary]") {

  std::string fileName = relativePath + "arial.png";

  std::unique_ptr<nbt::binary::FileReader> br;

  br.reset(new nbt::binary::FileReader(fileName, nbt::binary::EndiannessBig));

  REQUIRE(br->isOpen());

  SECTION("shouldStoreFileName") {
    CHECK_THAT(br->getFileName().c_str(), Catch::Equals(fileName.c_str()));
  }

  SECTION("shouldIndicateFileOpenStatus") {
    nbt::binary::FileReader invalidBr("oeu.oeu");
    CHECK(invalidBr.isOpen() == false);
    CHECK(br->isOpen() == true);
  }

  SECTION("shouldBeAbleToReadAllBytesOfFile") {
    nbt::binary::FileReader binFile(relativePath + "FileSampleDoc.txt");

    REQUIRE(binFile.isOpen() == true);

    auto bytes = binFile.getBytes();

    char const text[] = "This is merely a text file containing random "
                        "stuff.\r\n\r\nPoint\r\n0.0, 1.0, 2.0\r\n\r\nAnother "
                        "point\r\n3.0, 4.0, 5.0";

    for (int i = 0; i < bytes.size(); i++) {
      CHECK(bytes[i] == text[i]);
    }
    int x = 0;
  }

  SECTION("shouldBeAbleToReadStrings") {
    REQUIRE(br->isOpen() == true);

    char signature = '\x89';

    char fileSignature = br->get_next<char>();

    CHECK(fileSignature == signature);

    CHECK_THAT(br->get_next_n<std::string>(1).c_str(), Catch::Equals("P"));
    CHECK_THAT(br->get_next_n<std::string>(1).c_str(), Catch::Equals("N"));
    CHECK_THAT(br->get_next_n<std::string>(1).c_str(), Catch::Equals("G"));

    br->skip(8);
    CHECK(br->get_next<char>() == 'I');
    CHECK(br->get_next<char>() == 'H');
    CHECK(br->get_next<char>() == 'D');
    CHECK(br->get_next<char>() == 'R');
  }

  SECTION("shouldBeAbleToReadBuiltInTypes") {
    REQUIRE(br->isOpen() == true);
    // Skip the header
    br->skip(16);

    int imgWidth = br->get_next<int>();

    CHECK(imgWidth == 512);

    int imgHeight = br->get_next<int>();

    CHECK(imgHeight == 512);
  }

  SECTION("readingCustomFile") {
    // This file contains sections that are written in
    // both big and little endian.

    // Big endian section
    nbt::binary::FileReader brb(
        relativePath + "myBinFile.bin", nbt::binary::EndiannessBig);

    REQUIRE(brb.isOpen() == true);

    brb.skip(sizeof(int));

    int x1 = brb.get_next<int>();

    CHECK(x1 == 5);

    unsigned x2 = brb.get_next<unsigned>();

    CHECK(x2 == 10);

    double x3 = brb.get_next<double>();

    CHECK(x3 == 0.50);

    float x4 = brb.get_next<float>();

    CHECK(x4 == 0.50f);

    CHECK(0.50 == 0.50F);

    brb.close();

    // Little endian section
    nbt::binary::FileReader brl(
        relativePath + "myBinFile.bin", nbt::binary::EndiannessLittle);

    brl.skip(sizeof(int));
    brl.skip(sizeof(int));
    brl.skip(sizeof(unsigned));
    brl.skip(sizeof(double));
    brl.skip(sizeof(float));

    x1 = brl.get_next<int>();

    CHECK(x1 == 5);

    x2 = brl.get_next<unsigned>();

    CHECK(x2 == 10);

    x3 = brl.get_next<double>();

    CHECK(x3 == 0.50);

    x4 = brl.get_next<float>();

    CHECK(x4 == 0.50f);

    CHECK(0.50 == 0.50F);
  }
}
