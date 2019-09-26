#pragma once

#include <nbt/graphics/Shader.hpp>

class ShaderMock : public nbt::graphics::Shader {
public:
  ShaderMock(nbt::graphics::shader_type shaderType) : Shader(shaderType) {}

  ShaderMock(nbt::graphics::shader_type shaderType, std::string fileName)
      : Shader(shaderType, fileName) {}
  ~ShaderMock() {}

  void sendToGpu() {}
  unsigned int const getId() const {
    return static_cast<unsigned int>(0);
  }
};