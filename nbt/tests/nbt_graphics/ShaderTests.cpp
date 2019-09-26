#include "ShaderMock.hpp"
#include "gltTests.hpp"

#include <nbt/graphics/Shader.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Shader tests", "[nbt_graphics]") {
  std::unique_ptr<nbt::graphics::Shader> shader;

  SECTION("shouldStoreShaderType") {
    shader.reset(new ShaderMock(nbt::graphics::vertex));
    CHECK(shader->getType() == nbt::graphics::vertex);

    shader.reset(new ShaderMock(nbt::graphics::fragment));
    CHECK(shader->getType() == nbt::graphics::fragment);

    shader.reset(new ShaderMock(nbt::graphics::geometry));
    CHECK(shader->getType() == nbt::graphics::geometry);

    shader.reset(new ShaderMock(nbt::graphics::compute));
    CHECK(shader->getType() == nbt::graphics::compute);

    shader.reset(new ShaderMock(nbt::graphics::tesselation_control));
    CHECK(shader->getType() == nbt::graphics::tesselation_control);

    shader.reset(new ShaderMock(nbt::graphics::tesselation_evaluation));
    CHECK(shader->getType() == nbt::graphics::tesselation_evaluation);
  }

  SECTION("shouldBeAbleToInitializeSourceCodeWithFileName") {
    shader.reset(new ShaderMock(
        nbt::graphics::vertex, relPathToResFiles + "simple.vert.glsl"));

    const char * source = "#version 130\n"
                          "\n"
                          "attribute vec2 vPos;\n"
                          "attribute vec3 vCol;\n"
                          "\n"
                          "out vec3 vs_color;\n"
                          "void main(void)\n"
                          "{\n"
                          "	gl_Position = vec4(vPos, 1.0, 1.0);\n"
                          "   vs_color = vCol;\n"
                          "}\n";

    CHECK(shader->getSource() == source);
  }

  SECTION("shouldBeAbleToSetSourceCodeAfterDefaultInitialization") {
    const char * source = "#version 130\n"
                          "\n"
                          "attribute vec2 vPos;\n"
                          "attribute vec3 vCol;\n"
                          "\n"
                          "out vec3 vs_color;\n"
                          "void main(void)\n"
                          "{\n"
                          "	gl_Position = vec4(vPos, 1.0, 1.0);\n"
                          "   vs_color = vCol;\n"
                          "}\n";

    shader.reset(new ShaderMock(nbt::graphics::vertex));

    shader->setSource(source);

    CHECK_THAT(shader->getSource().c_str(), Catch::Equals(source));
  }

  SECTION("shouldStoreShaderId") {
    shader.reset(new ShaderMock(nbt::graphics::vertex));
    CHECK(shader->getId() == 0);
  }
}
