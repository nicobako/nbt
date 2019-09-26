#include <fstream>
#include <nbt/graphics/Shader.hpp>

#include <GL/glew.h>

namespace nbt {
namespace graphics {
Shader::Shader(shader_type shaderType)
    : shaderType_(shaderType), source_(), id_(0), errorMessage_(),
      sentToGpu_(false) {}

Shader::Shader(shader_type shaderType, std::string const & fileName)
    : shaderType_(shaderType), source_(), id_(0), errorMessage_(),
      sentToGpu_(false) {
  loadSourceFromFile(fileName);
}

Shader::~Shader() {
  if (this->sentToGpu())
    glDeleteShader(this->getId());
}

shader_type const Shader::getType() const {
  return shaderType_;
}

std::string const & Shader::getSource() const {
  return source_;
}

void Shader::setSource(std::string const & source) {
  source_ = source;
}

void Shader::loadSourceFromFile(std::string const & fileName) {
  std::ifstream stream(fileName);

  if (!stream.good())
    return;

  source_ = std::string(
      std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());

  stream.close();
}

void Shader::sendToGpu() {
  // first determine the GLenum that
  // represents the shader type
  GLenum shaderType =
      (shaderType_ == vertex)
          ? GL_VERTEX_SHADER
          : (shaderType_ == fragment)
                ? GL_FRAGMENT_SHADER
                : (shaderType_ == geometry)
                      ? GL_GEOMETRY_SHADER
                      : (shaderType_ == compute)
                            ? GL_COMPUTE_SHADER
                            : (shaderType_ == tesselation_control)
                                  ? GL_TESS_CONTROL_SHADER
                                  : (shaderType_ == tesselation_evaluation)
                                        ? GL_TESS_EVALUATION_SHADER
                                        : GL_INVALID_ENUM;

  id_ = glCreateShader(shaderType);

  const char * source[] = {" "};
  source[0] = getSource().c_str();

  glShaderSource(id_, 1, source, NULL);
  glCompileShader(id_);

  GLint success;
  glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint infoLogLength;
    glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &infoLogLength);
    GLchar * buffer = new GLchar[infoLogLength];
    GLsizei bufferSize;
    glGetShaderInfoLog(id_, infoLogLength, &bufferSize, buffer);
    errorMessage_ = buffer;
    delete[] buffer;

    sentToGpu_ = false;
  } else
    sentToGpu_ = true;
}
bool Shader::sentToGpu() const {
  return sentToGpu_;
}
std::string const & Shader::getErrorMessage() const {
  return errorMessage_;
}

unsigned const Shader::getId() const {
  return id_;
}
} // namespace graphics
} // namespace nbt
