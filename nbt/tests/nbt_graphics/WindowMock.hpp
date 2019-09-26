#include <nbt/graphics/Window.hpp>

class WindowMock : public nbt::graphics::Window {
public:
  WindowMock(std::string const & title, int width, int height)
      : nbt::graphics::Window(title, width, height) {}
  WindowMock(
      std::string const & title,
      int width,
      int height,
      glm::vec3 const & backgroundColor)
      : nbt::graphics::Window(title, width, height, backgroundColor) {}
  void drawBackground() const {}
  void swapBuffers() {}
  void pollEvents() {}
  void pollEvents(nbt::graphics::Camera & camera) {}
  void initializeGui() {}
  void getOpenGlContext() {}
  void initializeGlew() {}
};
