#pragma once

#include <nbt/graphics/Direction.hpp>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace nbt {
namespace graphics {
/// \brief Represents a camera by which a 3D scene is viewed.
///
/// A camera has an *eye* (the physical position of the lense),
/// and a *center* (the physical position that the camera is pointed to).
class Camera {
public:
  /// \brief Camera constructor
  ///
  /// \param sensitivity The angle in degrees by which the camera moves
  ///        each time a *move* command is issued.
  Camera(
      float sensitivity_degrees = 0.5f,
      glm::vec3 eye = glm::vec3(0.0f, 0.0f, 1.0f),
      glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f),
      float nearRange = 0.01f,
      float farRange = 2.0f,
      float fieldOfView_degrees = 60.0f);

  Camera(glm::vec3 eye, glm::vec3 center);

  /// \returns The *eye* of the camera
  glm::vec3 const & eye() const;

  /// \returns the *center* of the camera
  glm::vec3 const & center() const;

  /// \return the *near range* of the camera
  float const nearRange() const;

  /// \return the *far range* of the camera
  float const farRange() const;

  /// \returns the *up* vector of the camera
  glm::vec3 const & up() const;

  /// \returns the *right* vector of the camera
  glm::vec3 const & right() const;

  /// \returns A modifiable reference to the aspect ratio
  float & aspectRatio();
  /// \brief Rotate the *eye* of the camera
  ///        around the *center* of the camera
  ///
  /// If the camera were pointing towards a bowl of apples on a table,
  /// this would be analogous to moving around the table while
  /// always keeping the camera pointed and focused on the
  /// bowl of apples.
  ///
  /// \note This function can take the following directions:
  ///       - right
  ///       - left
  ///       - up
  ///       - down
  void arc(Direction const & direction);

  /// \brief Tilts the camera without moving the camera *eye*
  ///
  /// This motion is analogous to tilting your head up or down,
  /// or turning your head right or left.
  ///
  /// \note This function can take the following directions:
  ///       - right
  ///       - left
  ///       - up
  ///       - down
  void pan(Direction const & direction);

  /// \brief Moves both the *eye* and the *center* of the camera together.
  ///
  /// This is analogous to putting the camera on a mobile platform
  /// and moving the platform in a straight line.
  void dolly(Direction const & direction);

  /// \returns the view matrix
  glm::mat4 const lookAtMatrix() const;

  /// \returns The perspective matrix
  glm::mat4 const perspectiveMatrix() const;

private:
  /// \brief Updates the up and right vectors
  void update();

  /// \brief The angle that the camera moves.
  float sensitivity_;

  /// \brief The near range of the camera.
  float nearRange_;
  /// \brief The far range of the camera.
  float farRange_;

  /// \brief The field of view of the camera.
  float fieldOfView_;

  /// \brief The aspect ratio of the window.
  ///
  /// This is updated every time the user calls
  /// Window::pollEvents(Camera& camera)
  float aspectRatio_;

  /// \brief The field of view
  /// \brief The *position* of the camera
  ///
  /// This is where the of the camera appears to be in 3D space.
  glm::vec3 eye_;

  /// \brief The *focal* point of the camera
  ///
  /// This is where the camera is pointing in 3D space.
  glm::vec3 center_;

  glm::vec3 up_;
  glm::vec3 right_;
};
} // namespace graphics
} // namespace nbt