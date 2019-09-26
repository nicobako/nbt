#include <nbt/graphics/GlfwWindow.hpp>

#include <GL/glew.h>

namespace nbt {
namespace graphics {

GlfwWindow::GlfwWindow(
    std::string const & title,
    int width,
    int height,
    glm::vec3 const & backgroundColor)
    : Window(title, width, height, backgroundColor), guiInitialized_(false),
      glewInitialized_(false), window_(nullptr), closed_(false) {
  initializeGui();

  if (!guiInitialized_)
    return;

  getOpenGlContext();

  initializeGlew();

  if (glewInitialized_)
    closed_ = false;
}

GlfwWindow::~GlfwWindow() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

bool GlfwWindow::isInitialized() const {
  return guiInitialized_;
}
void GlfwWindow::initializeGui() {
  if (glfwInit()) {
    window_ = glfwCreateWindow(
        this->getWidth(),
        this->getHeight(),
        this->getTitle().c_str(),
        NULL,
        NULL);
    guiInitialized_ = true;
  } else
    guiInitialized_ = false;
}

void GlfwWindow::getOpenGlContext() {
  glfwMakeContextCurrent(window_);
}

void GlfwWindow::initializeGlew() {
  GLenum glewStatus = glewInit();
  if (glewStatus != GLEW_OK)
    glewInitialized_ = false;

  else
    glewInitialized_ = true;
}
void GlfwWindow::enable(GLenum cap) const {
  glEnable(cap);
}

void GlfwWindow::clear(GLbitfield bitfield) const {
  glClear(bitfield);
}
void GlfwWindow::drawBackground() const {
  glClearColor(
      this->getBackgroundColor().r,
      this->getBackgroundColor().g,
      this->getBackgroundColor().b,
      1.0f);

  glClear(GL_COLOR_BUFFER_BIT);
  glViewport(0, 0, getWidth(), getHeight());
}
void GlfwWindow::swapBuffers() {
  glfwSwapBuffers(window_);
}

void GlfwWindow::pollEvents() {
  glfwPollEvents();

  // get the width/height of the window
  int width, height;
  glfwGetWindowSize(window_, &width, &height);
  setWidth(width);
  setHeight(height);
}

void GlfwWindow::pollEvents(Camera & camera) {
  this->pollEvents();

  camera.aspectRatio() = Window::aspectRatio();

  // camera movements
  auto leftCtrlKeyStatus = glfwGetKey(this->window_, GLFW_KEY_LEFT_CONTROL);

  auto leftShiftKeyStatus = glfwGetKey(this->window_, GLFW_KEY_LEFT_SHIFT);

  if (leftCtrlKeyStatus == GLFW_PRESS) {
    auto panCameraIfKeyPressed =
        [this,
         &camera](int glfwKey, nbt::graphics::Direction direction) -> bool {
      auto keyState = glfwGetKey(this->window_, glfwKey);
      if (keyState == GLFW_PRESS) {
        camera.pan(direction);
        return true;
      } else {
        return false;
      }
    };
    panCameraIfKeyPressed(GLFW_KEY_LEFT, left);
    panCameraIfKeyPressed(GLFW_KEY_RIGHT, right);
    panCameraIfKeyPressed(GLFW_KEY_DOWN, down);
    panCameraIfKeyPressed(GLFW_KEY_UP, up);
  } else if (leftShiftKeyStatus == GLFW_PRESS) {
    auto dollyCameraIfKeyPressed =
        [this,
         &camera](int glfwKey, nbt::graphics::Direction direction) -> bool {
      auto keyState = glfwGetKey(this->window_, glfwKey);
      if (keyState == GLFW_PRESS) {
        camera.dolly(direction);
        return true;
      } else {
        return false;
      }
    };
    dollyCameraIfKeyPressed(GLFW_KEY_LEFT, left);
    dollyCameraIfKeyPressed(GLFW_KEY_RIGHT, right);
    dollyCameraIfKeyPressed(GLFW_KEY_UP, forward);
    dollyCameraIfKeyPressed(GLFW_KEY_DOWN, backward);
  } else {

    auto arcCameraIfKeyPressed =
        [this,
         &camera](int glfwKey, nbt::graphics::Direction direction) -> bool {
      auto keyState = glfwGetKey(this->window_, glfwKey);
      if (keyState == GLFW_PRESS) {
        camera.arc(direction);
        return true;
      } else {
        return false;
      }
    };

    arcCameraIfKeyPressed(GLFW_KEY_LEFT, left);
    arcCameraIfKeyPressed(GLFW_KEY_RIGHT, right);
    arcCameraIfKeyPressed(GLFW_KEY_DOWN, down);
    arcCameraIfKeyPressed(GLFW_KEY_UP, up);
  }
}

bool GlfwWindow::isClosed() {
  if (glfwWindowShouldClose(window_)) {
    return true;
  } else {
    return false;
  }
}

} // namespace graphics
} // namespace nbt
