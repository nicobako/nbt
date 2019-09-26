#pragma once

#include <vector>

#include <nbt/graphics/Camera.hpp>
#include <nbt/graphics/Shader.hpp>

#include <glm/mat4x4.hpp>

namespace nbt {
namespace graphics {
/// \brief Represents an OpenGL program.
///
/// The Program class
class Program {
public:
  /// \brief Default ctor
  Program();
  /// \brief Default dtor
  virtual ~Program();
  /// \brief Returns the id/name OpenGL assigned to the program
  unsigned int const getId() const;
  /// \brief Attaches a shader to the program
  void attach(Shader const & shader);
  /// \brief Sends the program to the GPU to get compiled
  virtual void sendToGpu();
  /// \brief Returns a bool indicating if the program was sent to GPU
  bool sentToGpu() const;
  /// \brief Uses the program for drawing
  ///
  /// This must be called before you can draw anything with the program
  virtual void use() const;
  /// \brief Returns error that may have occured during this->sendToGpu()
  std::string const & getErrorMessage();

  /// \brief Updates the OpenGL uniforms that are part of the program
  ///
  /// In order for this function to work properly shaders must already
  /// be attached to the program (\see Program::attach()),
  /// the program must already be sent to the GPU (\see Program::sendToGpu()).
  void updateUniform(std::string const & uniformName, glm::mat4 const & matrix);

private:
  /// \brief the id/name of the program generated by OpenGL
  unsigned int id_;
  /// \brief The shader ids/names attached to the Program
  std::vector<unsigned int> shaderIds_;
  /// \brief A bool indicating if the program was sent to the GPU
  bool sentToGpu_;
  /// \brief The error message generated during this->sendToGpu()
  std::string errorMessage_;
};
} // namespace graphics
} // namespace nbt
