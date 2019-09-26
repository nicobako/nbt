#include "WindowMock.hpp"
#include "gltTests.hpp"

#include <nbt/core/random.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Window tests", "[nbt_graphics]") {

  std::string title = nbt::core::random<std::string>();

  nbt::core::ValueRange<int> range(1, 1000);
  int width = nbt::core::random<int>(range);
  int height = nbt::core::random<int>(range);

  std::unique_ptr<nbt::graphics::Window> window(
      new WindowMock(title, width, height));

  SECTION("shouldBeInitializedWithTitleWidthAndHeight") {
    window.reset(new WindowMock(title, width, height));

    CHECK_THAT(window->getTitle().c_str(), Catch::Equals(title.c_str()));
    CHECK(window->getWidth() == width);
    CHECK(window->getHeight() == height);
  }

  SECTION("shouldBeAbleToChangeWidth") {
    int newWidth = nbt::core::random<int>();
    window->setWidth(newWidth);
    CHECK(window->getWidth() == newWidth);
  }

  SECTION("shouldBeAbleToChangeHeight") {
    int newHeight = nbt::core::random<int>();
    window->setHeight(newHeight);
    CHECK(window->getHeight() == newHeight);
  }

  SECTION("shouldHaveDefaultWhiteBackground") {
    glm::vec3 white(1.0f, 1.0f, 1.0f);
    CHECK(window->getBackgroundColor() == white);
  }

  SECTION("shouldBeAbleToInitializeWithBackgroundColor") {
    nbt::core::ValueRange<float> colorRange(0.0f, 1.0f);
    float r = nbt::core::random<float>(colorRange);
    float g = nbt::core::random<float>(colorRange);
    float b = nbt::core::random<float>(colorRange);
    auto color = glm::vec3(r, g, b);

    window.reset(new WindowMock(title, width, height, color));
    CHECK(window->getBackgroundColor() == color);
  }

  SECTION("shouldBeAbleToChangeBackgroundColor") {
    nbt::core::ValueRange<float> colorRange(0.0f, 1.0f);
    float r = nbt::core::random<float>(colorRange);
    float g = nbt::core::random<float>(colorRange);
    float b = nbt::core::random<float>(colorRange);
    auto color = glm::vec3(r, g, b);
    window->setBackgroundColor(color);
    CHECK(window->getBackgroundColor() == color);
  }
}
