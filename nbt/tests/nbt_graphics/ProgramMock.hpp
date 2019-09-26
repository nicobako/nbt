#include "gltTests.hpp"

#include <nbt/graphics/Program.hpp>

class ProgramMock : public nbt::graphics::Program {
public:
  ProgramMock() : Program(), shaderAttached(false) {}
  ~ProgramMock() {}
  void sendtoGpu() {}
  void updateUniforms(nbt::graphics::Camera const & camera) {}
  bool shaderAttached;
  void attach(nbt::graphics::Shader const & shader) {
    Program::attach(shader);
    this->shaderAttached = true;
  }

private:
};