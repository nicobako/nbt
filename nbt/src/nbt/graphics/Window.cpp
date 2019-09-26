#include <nbt/graphics/Window.hpp>

#include <glm/gtx/transform.hpp>

namespace nbt {
namespace graphics {
Window::Window(
    std::string const & title,
    int width,
    int height,
    glm::vec3 const & backgroundColor)
    : title_(title), width_(width), height_(height),
      backgroundColor_(backgroundColor) {}

Window::~Window() {}

std::string const & Window::getTitle() const {
  return title_;
}

int Window::getWidth() const {
  return width_;
}
void Window::setWidth(int width) {
  width_ = width;
}

int Window::getHeight() const {
  return height_;
}
void Window::setHeight(int height) {
  height_ = height;
}

float Window::aspectRatio() const {
  return static_cast<float>(this->width_) / static_cast<float>(this->height_);
}

glm::vec3 const & Window::getBackgroundColor() const {
  return backgroundColor_;
}

void Window::setBackgroundColor(glm::vec3 const & color) {
  backgroundColor_ = color;
}
} // namespace graphics
} // namespace nbt
