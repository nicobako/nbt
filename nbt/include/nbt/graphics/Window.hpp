#pragma once

#include <string>

#include <nbt/graphics/Camera.hpp>

#include <glm/vec3.hpp>

namespace nbt {
namespace graphics {
/// \brief Abstract class that represents a GUI window
///
/// This class can be derived from and used to create
/// a window that the user can interact with to visualize
/// 3D data. The pure virtual functions must be overriden
/// and implemented in the derived class.
class Window {
public:
  /// \brief Constructor of the window
  Window(
      std::string const & title,
      int width,
      int height,
      glm::vec3 const & backgroundColor = glm::vec3(1.0f, 1.0f, 1.0f));

  virtual ~Window();
  std::string const & getTitle() const;

  int getWidth() const;
  void setWidth(int width);

  int getHeight() const;
  void setHeight(int height);

  glm::vec3 const & getBackgroundColor() const;
  void setBackgroundColor(glm::vec3 const & color);

  float aspectRatio() const;

  /// \brief Draws the background color
  ///
  /// This function is called at the beginning of every
  /// while(!window.isClosed{...} loop
  virtual void drawBackground() const = 0;

  /// \brief This is where the user swaps the buffer after draw calls
  virtual void swapBuffers() = 0;

  /// \brief This is where the user will respond to input
  ///        such as mouse/keyboard input
  ///        that only effects the window itself.
  virtual void pollEvents() = 0;

  /// \brief This is where the user will respond to input
  ///        such as mouse/keyboard input,
  ///        that effects the \p camera.
  virtual void pollEvents(Camera & camera) = 0;

private:
  /// The title of the window
  std::string title_;
  /// The width and height of the window
  int width_, height_;
  /// The background color of the window
  glm::vec3 backgroundColor_;

  // Pure virtual member functions
  // These should be called in the order listed below
  // None of these functions should throw, so they
  // should be able to be called in the constructor

  /// This is where the user will create the window
  /// by using/initializing the GUI library of their choice
  virtual void initializeGui() = 0;
  /// This is where the user gets the OpenGL context
  virtual void getOpenGlContext() = 0;
  /// This is where the user will initialize glew
  virtual void initializeGlew() = 0;
};
} // namespace graphics
} // namespace nbt
