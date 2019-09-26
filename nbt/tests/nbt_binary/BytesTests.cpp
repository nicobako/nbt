#include "BinaryTests.hpp"

#include <array>
#include <cstring>
#include <iomanip>

#include <nbt/binary/Bytes.hpp>
#include <nbt/core/random.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Bytes tests", "[nbt_binary]") {

  nbt::binary::Bytes bytes;
  int num_i = nbt::core::random<int>();
  double num_d = nbt::core::random<double>();

  SECTION("shouldBeAbleToCopyBytesFromTypesIntoBytesContainer") {
    nbt::binary::copy_bytes(bytes, num_i);

    std::array<nbt::binary::Byte, 4> buffer_int;
    std::memcpy(&buffer_int[0], &num_i, sizeof num_i);

    REQUIRE(bytes.size() == 4);
    for (int i = 0; i < sizeof(int); i++) {
      CHECK(bytes.at(i) == buffer_int.at(i));
    }

    bytes.clear();
    nbt::binary::copy_bytes(bytes, num_d);

    std::array<nbt::binary::Byte, sizeof(double)> buffer_double;
    std::memcpy(&buffer_double[0], &num_d, sizeof(double));

    REQUIRE(bytes.size() == sizeof(double));
    for (int i = 0; i < sizeof(double); i++) {
      CHECK(bytes[i] == buffer_double[i]);
    }
  }

  SECTION("shouldBeAbleToCopyVectorOfTypesIntoBytesContainer") {
    std::vector<int> vec_i;
    int const length = 100;
    for (int i = 0; i < length; i++) {
      vec_i.push_back(nbt::core::random<int>());
    }

    nbt::binary::copy_bytes(bytes, vec_i);

    std::array<nbt::binary::Byte, length * sizeof(int)> buffer_i;

    REQUIRE(bytes.size() == buffer_i.size());

    for (int i = 0; i < length; i++) {
      std::memcpy(&buffer_i[i * sizeof(int)], &vec_i[i], sizeof(int));
    }

    for (int i = 0; i < length * sizeof(int); i++) {
      CHECK(bytes[i] == buffer_i[i]);
    }

    // std::copy(
    //	bytes.begin(),
    //	bytes.end(),
    //	std::ostream_iterator<int>(std::cout << std::hex, " ") );
    //
    // std::cout << std::resetiosflags(std::ios_base::basefield);
  }

  SECTION("shouldBeAbleToIterateOverBytesAsIfTheyWereBuiltInType") {
    auto slice = nbt::core::slice<int>(nbt::core::ValueRange<int>(0, 10), 1);

    nbt::binary::Bytes bytes;
    nbt::binary::copy_bytes(bytes, slice);

    auto bytes_as_ints = nbt::binary::convert_to<int>(bytes);

    REQUIRE(bytes_as_ints.size() == slice.size());

    CHECK(std::equal(slice.begin(), slice.end(), bytes_as_ints.begin()));
  }

  SECTION("shouldBeAbleToConvertBytesToString") {
    nbt::core::ValueRange<char> letters('a', 'z');
    auto lettersVec = nbt::core::slice(letters, char(1));

    nbt::binary::Bytes bytes;
    nbt::binary::copy_bytes(bytes, lettersVec);

    auto lettersString = nbt::binary::convert_to_string(bytes);

    REQUIRE(lettersString.size() == lettersVec.size());

    for (int i = 0; i < lettersVec.size(); i++) {
      CHECK(lettersString[i] == lettersVec[i]);
    }
  }
}
