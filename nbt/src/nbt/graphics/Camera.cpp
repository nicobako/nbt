#include <iostream>

#include <nbt/graphics/Camera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/vec3.hpp>

namespace nbt {
namespace graphics {
Camera::Camera(
    float sensitivity_degrees,
    glm::vec3 eye,
    glm::vec3 center,
    float nearRange,
    float farRange,
    float fieldOfView_degrees)
    : sensitivity_(glm::radians(sensitivity_degrees)), nearRange_(nearRange),
      farRange_(farRange), fieldOfView_(glm::radians(fieldOfView_degrees)),
      aspectRatio_(1.0f), eye_(eye), center_(center),
      right_(glm::vec3(1.0f, 0.0f, 0.0)), up_(glm::vec3(0.0f, 1.0f, 0.0f)) {
  this->update();
}

Camera::Camera(glm::vec3 eye, glm::vec3 center)
    : sensitivity_(0.005), nearRange_(0.001f),
      farRange_(glm::distance(eye, center) * 2.0f),
      fieldOfView_(glm::radians(60.0f)), aspectRatio_(1.0f), eye_(eye),
      center_(center), right_(glm::vec3(1.0f, 0.0f, 0.0)),
      up_(glm::vec3(0.0f, 1.0f, 0.0f)) {
  this->update();
}
glm::vec3 const & Camera::center() const {
  return this->center_;
}

float const Camera::nearRange() const {
  return this->nearRange_;
}

float const Camera::farRange() const {
  return this->farRange_;
}

glm::vec3 const & Camera::eye() const {
  return this->eye_;
}

glm::vec3 const & Camera::up() const {
  return this->up_;
}

glm::vec3 const & Camera::right() const {
  return this->right_;
}

void Camera::arc(Direction const & direction) {
  auto dirOfEye = this->eye_ - this->center_;

  auto dirOfNewEye = glm::vec3(0.0f, 0.0f, 0.0f);

  switch (direction) {
  case Direction::right:
    dirOfNewEye = glm::rotate(dirOfEye, sensitivity_, this->up_);
    break;

  case Direction::left:
    dirOfNewEye = glm::rotate(dirOfEye, -sensitivity_, this->up_);
    break;

  case Direction::up:
    dirOfNewEye = glm::rotate(dirOfEye, -sensitivity_, this->right_);
    break;

  case Direction::down:
    dirOfNewEye = glm::rotate(dirOfEye, sensitivity_, this->right_);
    break;

  default:
    break;
  }

  this->eye_ = this->center_ + dirOfNewEye;

  this->update();
}

float & Camera::aspectRatio() {
  return this->aspectRatio_;
}

void Camera::pan(Direction const & direction) {
  auto dirOfCenter = this->center_ - this->eye_;
  auto dirOfNewCenter = glm::vec3();

  switch (direction) {
  case Direction::right:
    dirOfNewCenter = glm::rotate(dirOfCenter, -sensitivity_, this->up_);

    break;

  case Direction::left:
    dirOfNewCenter = glm::rotate(dirOfCenter, sensitivity_, this->up_);

    break;

  case Direction::up:
    dirOfNewCenter = glm::rotate(dirOfCenter, sensitivity_, this->right_);

    break;

  case Direction::down:
    dirOfNewCenter = glm::rotate(dirOfCenter, -sensitivity_, this->right_);

    break;

  default:
    break;
  }

  center_ = this->eye_ + dirOfNewCenter;
  this->update();
}

void Camera::dolly(Direction const & direction) {
  auto dirToMove = glm::vec3(0.0f, 0.0f, 0.0f);

  auto const radius = glm::distance(this->eye_, this->center_);

  auto computeDirToMove = [&radius,
                           this](glm::vec3 const & refVec) -> glm::vec3 {
    return refVec * this->sensitivity_ * this->sensitivity_ * radius;
  };

  switch (direction) {
  case nbt::graphics::right:

    dirToMove = computeDirToMove(this->right_);

    break;
  case nbt::graphics::left:
    dirToMove = computeDirToMove(-this->right_);
    break;
  case nbt::graphics::up:
    dirToMove = computeDirToMove(this->up_);
    break;
  case nbt::graphics::down:
    dirToMove = computeDirToMove(-this->up_);
    break;
  case nbt::graphics::forward:
    dirToMove = computeDirToMove(this->center_ - this->eye_);
    break;
  case nbt::graphics::backward:
    dirToMove = computeDirToMove(this->eye_ - this->center_);
    break;
  default:
    break;
  }

  this->eye_ += dirToMove;
  this->center_ += dirToMove;

  auto print_vec3 = [](glm::vec3 v) {
    std::cout << v.x << " " << v.y << " " << v.z << "\n";
  };

  print_vec3(this->eye());
  print_vec3(this->center());
  print_vec3(this->right());
  print_vec3(this->up());

  this->update();
}

glm::mat4 const Camera::lookAtMatrix() const {
  return glm::lookAt(this->eye_, this->center_, this->up_);
}

glm::mat4 const Camera::perspectiveMatrix() const {
  return glm::perspective(
      this->fieldOfView_,
      this->aspectRatio_,
      this->nearRange_,
      this->farRange_);
}

void Camera::update() {
  auto direction = glm::normalize(this->eye_ - this->center_);

  this->right_ = glm::normalize(glm::cross(this->up_, direction));

  this->up_ = glm::cross(direction, this->right_);
}

} // namespace graphics
} // namespace nbt