#include <algorithm>
#include <iterator>

#include <nbt/graphics/Program.hpp>

#include <GL/glew.h>

namespace nbt {
namespace graphics {
Program::Program() : id_(), shaderIds_(), sentToGpu_(false), errorMessage_() {
  // id_ = glCreateProgram();
}
Program::~Program() {
  if (this->sentToGpu()) {
    std::for_each(
        shaderIds_.begin(),
        shaderIds_.end(),
        [this](unsigned int const shaderId) {
          glDetachShader(this->getId(), shaderId);
        });

    glDeleteProgram(this->getId());
  }
}

unsigned int const Program::getId() const {
  return id_;
}

void Program::attach(Shader const & shader) {
  // glAttachShader(this->id_, shader.getId());
  shaderIds_.push_back(shader.getId());
}

void Program::sendToGpu() {
  id_ = glCreateProgram();

  std::for_each(
      shaderIds_.begin(),
      shaderIds_.end(),
      [this](unsigned int const shaderId) {
        glAttachShader(this->getId(), shaderId);
      });

  glLinkProgram(this->getId());

  GLint sentToGpu = 0;
  glGetProgramiv(this->getId(), GL_LINK_STATUS, &sentToGpu);
  if (sentToGpu == GL_FALSE) {
    GLint length = 0;
    glGetProgramiv(this->getId(), GL_INFO_LOG_LENGTH, &length);
    std::vector<GLchar> infoLog(length);
    GLsizei bufferSize;
    glGetProgramInfoLog(this->getId(), length, &bufferSize, &infoLog[0]);

    glDeleteProgram(this->getId());

    std::copy(
        infoLog.begin(), infoLog.end(), std::back_inserter(errorMessage_));
  } else {
    this->errorMessage_.clear();
    this->sentToGpu_ = true;
  }
}
std::string const & Program::getErrorMessage() {
  return errorMessage_;
}
bool Program::sentToGpu() const {
  return sentToGpu_;
}
void Program::use() const {
  glUseProgram(this->getId());
}

void Program::updateUniform(
    std::string const & uniformName,
    glm::mat4 const & matrix) {
  GLint matrixLocation =
      glGetUniformLocation(this->getId(), uniformName.c_str());

  glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &matrix[0][0]);
}

} // namespace graphics
} // namespace nbt