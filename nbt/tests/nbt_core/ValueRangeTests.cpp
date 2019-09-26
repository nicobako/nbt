#include <nbt/core/ValueRange.hpp>

#include <catch2/catch.hpp>

TEST_CASE("ValueRange", "[nbt_core]") {
  SECTION("shouldBeAbleToRetrieveFirstValue") {
    nbt::core::ValueRange<int> range(0, 10);
    CHECK(range.first() == 0);
  }

  SECTION("shouldBeAbleToRetrieveSecondValue") {
    nbt::core::ValueRange<int> range(0, 10);
    CHECK(range.second() == 10);
  }

  SECTION("shouldSetMinProperly") {
    nbt::core::ValueRange<int> rangeInt(0, 10);
    CHECK(rangeInt.minimum() == 0);

    nbt::core::ValueRange<int> rangeIntReverse(10, 0);
    CHECK(rangeIntReverse.minimum() == 0);

    nbt::core::ValueRange<char> rangeChar('a', 'd');
    CHECK(rangeChar.minimum() == 'a');

    nbt::core::ValueRange<char> rangeCharReverse('d', 'a');
    CHECK(rangeCharReverse.minimum() == 'a');
  }

  SECTION("shouldSetMaxNamedType") {
    nbt::core::ValueRange<int> rangeInt(0, 10);
    CHECK(rangeInt.maximum() == 10);

    nbt::core::ValueRange<int> rangeIntReverse(10, 0);
    CHECK(rangeIntReverse.maximum() == 10);

    nbt::core::ValueRange<char> rangeChar('a', 'd');
    CHECK(rangeChar.maximum() == 'd');

    nbt::core::ValueRange<char> rangeCharReverse('d', 'a');
    CHECK(rangeCharReverse.maximum() == 'd');
  }

  SECTION("shouldAcceptRangesWhereMinAndMaxAreEqual") {
    nbt::core::ValueRange<int> range(0, 0);

    CHECK(range.maximum() == range.minimum());
  }

  SECTION("shouldIndicateWhetherAvalueIsInTheRange") {
    nbt::core::ValueRange<int> range(0, 10);

    nbt::core::NamedType<int> negOne(-1);
    nbt::core::NamedType<int> zero(0);
    nbt::core::NamedType<int> five(5);
    nbt::core::NamedType<int> ten(10);
    nbt::core::NamedType<int> eleven(11);

    CHECK(nbt::core::isInRange(negOne, range) == false);
    CHECK(nbt::core::isInRange(-1, range) == false);
    CHECK(nbt::core::isInRange(zero, range) == true);
    CHECK(nbt::core::isInRange(0, range) == true);
    CHECK(nbt::core::isInRange(five, range) == true);
    CHECK(nbt::core::isInRange(5, range) == true);
    CHECK(nbt::core::isInRange(ten, range) == true);
    CHECK(nbt::core::isInRange(10, range) == true);
    CHECK(nbt::core::isInRange(eleven, range) == false);
    CHECK(nbt::core::isInRange(11, range) == false);
  }

  SECTION("shouldComputeSpanOfMinAndMaxNamedTypes") {
    nbt::core::ValueRange<int> range(0, 10);
    CHECK(range.getSpan() == 10);

    nbt::core::ValueRange<int> rangeRev(10, 0);
    CHECK(rangeRev.getSpan() == -10);
  }

  SECTION("shouldBeAbleToSliceRangeByPositiveIncrement") {
    float increment = 0.5f;
    float min = 0.0f;
    float max = 5.0f;

    nbt::core::ValueRange<float> range(min, max);

    auto slicedRange = slice(range, increment);

    int numElementShouldBeInSlicedRange = (range.getSpan() / increment) + 1;

    REQUIRE(slicedRange.size() == numElementShouldBeInSlicedRange);

    float val = min;
    for (int i = 0; i < slicedRange.size(), i++;) {
      val += static_cast<float>(i) * increment;
      CHECK(slicedRange[i] == val);
    }
  }

  SECTION("shouldBeAbleToSliceRangeByNegativeIncrement") {
    float increment = -0.5f;
    float min = 0.0f;
    float max = 5.0f;

    nbt::core::ValueRange<float> range(max, min);

    auto slicedRange = nbt::core::slice(range, increment);

    int numElementShouldBeInSlicedRange = (range.getSpan() / increment) + 1;

    REQUIRE(slicedRange.size() == numElementShouldBeInSlicedRange);

    float val = max;
    for (int i = 0; i < slicedRange.size(), i++;) {
      val -= static_cast<float>(i) * increment;
      CHECK(slicedRange[i] == val);
    }
  }

  SECTION("shouldReturnSliceSizeZeroIfSpanOfRangeIsZero") {
    nbt::core::ValueRange<float> range(0.0f, 0.0f);

    auto slicedRange = nbt::core::slice(range, 0.01f);

    CHECK(slicedRange.size() == 0);
  }

  SECTION("shouldReturnSliceOgSizeZeroIfSpanIsPosButIncrementIsNeg") {
    // positive span, negative increment
    nbt::core::ValueRange<float> range(0.0f, 10.0f);
    auto slicedRange = nbt::core::slice(range, -0.01f);
    CHECK(slicedRange.size() == 0);
  }

  SECTION("shouldReturnSliceSizeOfZeroIfSpanIsNegButIncrementIsPos") {
    // positive span, negative increment
    nbt::core::ValueRange<float> range(10.0f, 0.0f);
    auto slicedRange = nbt::core::slice(range, 0.01f);
    CHECK(slicedRange.size() == 0);
  }
}
