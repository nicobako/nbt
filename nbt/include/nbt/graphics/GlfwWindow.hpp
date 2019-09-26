#pragma once

#include <string>

#include <nbt/graphics/Window.hpp> // base class nbt::graphics::Window

#include <GL/glew.h>    // MUST be included before glfw
#include <GLFW/glfw3.h> // GLFWwindow

namespace nbt {
namespace graphics {
class GlfwWindow : public Window {
public:
  GlfwWindow(
      std::string const & title,
      int width,
      int height,
      glm::vec3 const & backgroundColor = glm::vec3(1.0f, 1.0f, 1.0f));

  ~GlfwWindow();

  // This function reveals whether the GUI was properly created
  bool isInitialized() const;
  // This function reveals whether the GUI is closed
  bool isClosed();
  // This function is called at the beginning of every
  // while(!window.isClosed{/*...*/} loop
  void drawBackground() const override;
  // This is where the user swaps the buffer after draw calls
  virtual void swapBuffers() override;

  // This is where the user will respond to input
  // such as mouse/keyboard input
  virtual void pollEvents() override;

  virtual void pollEvents(Camera & camera) override;

  void enable(GLenum cap) const;
  void clear(GLbitfield cap) const;

private:
  bool guiInitialized_;
  bool glewInitialized_;
  GLFWwindow * window_;
  bool closed_;

  // This is where the GUI window gets created
  virtual void initializeGui() override;
  // This is where the user gets the OpenGL context
  virtual void getOpenGlContext() override;
  // This is where the user will initialize glew
  virtual void initializeGlew() override;
};
} // namespace graphics
} // namespace nbt
