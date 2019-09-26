#include "ProgramMock.hpp"
#include "ShaderMock.hpp"
#include "gltTests.hpp"

#include <nbt/graphics/Program.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Program tests", "[nbt_graphics]") {

  std::unique_ptr<ProgramMock> program(new ProgramMock());

  SECTION("shouldStoreAnIdAsUnsignedInt") {
    CHECK_NOTHROW(program->getId());

    CHECK(typeid(unsigned).name() == typeid(program->getId()).name());
  }

  SECTION("shouldBeAbleToAttachShader") {
    ShaderMock vertexShader(nbt::graphics::vertex);

    REQUIRE_FALSE(program->shaderAttached);

    program->attach(vertexShader);

    REQUIRE(program->shaderAttached);
  }

  SECTION("shouldStoreBoolIndicatingIfProperlySentToGpu") {
    CHECK(program->sentToGpu() == false);
  }
}