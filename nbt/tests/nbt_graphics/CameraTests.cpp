#include "gltTests.hpp"

#include <nbt/core/random.hpp>
#include <nbt/graphics/Camera.hpp>

#include <glm/gtx/rotate_vector.hpp>

#include <catch2/catch.hpp>

void expect_vec3_equal(glm::vec3 const & v1, glm::vec3 const & v2) {
  CHECK(v2.x == v1.x);
  CHECK(v2.y == v1.y);
  CHECK(v2.z == v1.z);
}

void expect_vec3_near(glm::vec3 const & v1, glm::vec3 const & v2, float error) {
  CHECK(v2.x == Approx(v1.x));
  CHECK(v2.y == Approx(v1.y));
  CHECK(v2.z == Approx(v1.z));
}

TEST_CASE("Camera tests", "[nbt_graphics]") {
  SECTION("shouldBeAbleToArcCameraEyeRightAndLeft") {
    auto sensitivity = 1.0f;

    auto camera = nbt::graphics::Camera(sensitivity);

    auto cameraCenter = camera.center();

    for (int i = 0; i < 100; ++i) {
      auto initialCameraEye = camera.eye();

      camera.arc(nbt::graphics::right);

      auto finalCameraEye = camera.eye();

      auto expectedFinalCameraEyePosition = glm::rotate(
          initialCameraEye,
          glm::radians(sensitivity),
          glm::vec3(0.0f, 1.0f, 0.0f));

      expect_vec3_equal(expectedFinalCameraEyePosition, finalCameraEye);
    }

    for (int i = 0; i < 100; ++i) {
      auto initialCameraEye = camera.eye();

      camera.arc(nbt::graphics::left);

      auto finalCameraEye = camera.eye();

      auto expectedFinalCameraEyePosition = glm::rotate(
          initialCameraEye,
          -glm::radians(sensitivity),
          glm::vec3(0.0f, 1.0f, 0.0f));

      expect_vec3_equal(expectedFinalCameraEyePosition, finalCameraEye);
    }
  }

  SECTION("shouldBeAbleTArcCameraEyeUpAndDown") {
    auto sensitivity = 1.0f;

    auto camera = nbt::graphics::Camera(sensitivity);

    auto cameraCenter = camera.center();

    for (int i = 0; i < 100; ++i) {
      auto initialCameraEye = camera.eye();

      camera.arc(nbt::graphics::up);

      auto finalCameraEye = camera.eye();

      auto expectedFinalCameraEyePosition = glm::rotate(
          initialCameraEye,
          -glm::radians(sensitivity),
          glm::vec3(1.0f, 0.0f, 0.0f));

      expect_vec3_equal(expectedFinalCameraEyePosition, finalCameraEye);
    }

    for (int i = 0; i < 100; ++i) {
      auto initialCameraEye = camera.eye();

      camera.arc(nbt::graphics::down);

      auto finalCameraEye = camera.eye();

      auto expectedFinalCameraEyePosition = glm::rotate(
          initialCameraEye,
          glm::radians(sensitivity),
          glm::vec3(1.0f, 0.0f, 0.0f));

      expect_vec3_equal(expectedFinalCameraEyePosition, finalCameraEye);
    }
  }

  SECTION("rightVectorShouldBeComputedProperly") {
    auto sensitivity = 1.0f;

    auto camera = nbt::graphics::Camera(sensitivity);
    auto up = camera.up();

    for (int i = 0; i < 100; ++i) {
      auto initialRight = camera.right();

      auto expectedFinalRight =
          glm::rotate(initialRight, glm::radians(sensitivity), up);

      camera.arc(nbt::graphics::right);

      expect_vec3_near(expectedFinalRight, camera.right(), 0.000001f);
    }
  }

  SECTION("shouldBeAbleToPanCameraRightAndLeft") {
    auto sensitivity = 0.10f;

    auto camera = nbt::graphics::Camera(sensitivity);

    auto const cameraEye = camera.eye();

    auto cameraUp = camera.up();

    // panning right
    for (int i = 0; i < 100; ++i) {
      auto initialRight = camera.right();

      auto expectedRight =
          glm::rotate(initialRight, -glm::radians(sensitivity), cameraUp);

      auto dirToCenter = camera.center() - camera.eye();

      auto expectedCenter =
          camera.eye()
          + glm::rotate(dirToCenter, -glm::radians(sensitivity), camera.up());

      camera.pan(nbt::graphics::right);

      expect_vec3_near(expectedRight, camera.right(), 0.0001f);

      expect_vec3_near(expectedCenter, camera.center(), 0.0001f);

      expect_vec3_equal(cameraEye, camera.eye());
    }

    for (int i = 0; i < 100; ++i) {
      auto initialRight = camera.right();

      auto expectedRight =
          glm::rotate(initialRight, glm::radians(sensitivity), cameraUp);

      auto dirToCenter = camera.center() - camera.eye();

      auto expectedCenter =
          camera.eye()
          + glm::rotate(dirToCenter, glm::radians(sensitivity), camera.up());

      camera.pan(nbt::graphics::left);

      expect_vec3_near(expectedRight, camera.right(), 0.0001f);

      expect_vec3_near(expectedCenter, camera.center(), 0.0001f);

      expect_vec3_equal(cameraEye, camera.eye());
    }
  }

  SECTION("shouldBeAbleToPanCameraUpAndDown") {
    auto sensitivity = 0.10f;

    auto camera = nbt::graphics::Camera(sensitivity);

    auto const cameraEye = camera.eye();

    auto cameraUp = camera.up();

    // panning up
    for (int i = 0; i < 100; ++i) {
      auto initialUp = camera.up();

      auto expectedUp =
          glm::rotate(initialUp, glm::radians(sensitivity), camera.right());

      auto dirToCenter = camera.center() - camera.eye();

      auto expectedCenter =
          camera.eye()
          + glm::rotate(dirToCenter, glm::radians(sensitivity), camera.right());

      camera.pan(nbt::graphics::up);

      expect_vec3_near(expectedUp, camera.up(), 0.001f);

      expect_vec3_near(expectedCenter, camera.center(), 0.0001f);

      expect_vec3_equal(cameraEye, camera.eye());
    }
    // panning down
    for (int i = 0; i < 100; ++i) {
      auto initialUp = camera.up();

      auto expectedUp =
          glm::rotate(initialUp, -glm::radians(sensitivity), camera.right());

      auto dirToCenter = camera.center() - camera.eye();

      auto expectedCenter =
          camera.eye()
          + glm::rotate(
                dirToCenter, -glm::radians(sensitivity), camera.right());

      camera.pan(nbt::graphics::down);

      expect_vec3_near(expectedUp, camera.up(), 0.001f);

      expect_vec3_near(expectedCenter, camera.center(), 0.0001f);

      expect_vec3_equal(cameraEye, camera.eye());
    }
  }

  SECTION("shouldBeAbleToDollyCameraInAllDirections") {
    auto const sensitivity = 0.5f;

    auto eyePos = glm::vec3(0.0f, 0.0f, 1.0f);
    auto centerPos = glm::vec3(0.0f, 0.0f, 0.0f);

    auto const radius = glm::distance(eyePos, centerPos);

    auto camera = nbt::graphics::Camera(sensitivity, eyePos, centerPos);

    auto computeDirToMove =
        [&radius, sensitivity](glm::vec3 const & refVec) -> glm::vec3 {
      return refVec * glm::radians(sensitivity) * glm::radians(sensitivity)
             * radius;
    };

    for (int i = 0; i < 100; ++i) {

      auto cameraCenter = camera.center();

      auto dirToMoveUP = computeDirToMove(camera.up());
      auto expectedEyeUp = camera.eye() + dirToMoveUP;
      auto expectedCenterUp = camera.center() + dirToMoveUP;

      camera.dolly(nbt::graphics::up);
      expect_vec3_near(expectedEyeUp, camera.eye(), 0.0001f);
      expect_vec3_near(expectedCenterUp, camera.center(), 0.0001f);

      auto dirToMoveDown = computeDirToMove(-camera.up());
      auto expectedEyeDown = camera.eye() + dirToMoveDown;
      auto expectedCenterDown = camera.center() + dirToMoveDown;
      camera.dolly(nbt::graphics::down);
      expect_vec3_near(expectedEyeDown, camera.eye(), 0.0001);
      expect_vec3_near(expectedCenterDown, camera.center(), 0.0001f);

      auto dirToMoveRight = computeDirToMove(camera.right());
      auto expectedEyeRight = camera.eye() + dirToMoveRight;
      auto expectedCenterRight = camera.center() + dirToMoveRight;
      camera.dolly(nbt::graphics::right);
      expect_vec3_near(expectedEyeRight, camera.eye(), 0.0001);
      expect_vec3_near(expectedCenterRight, camera.center(), 0.0001f);

      auto dirToMoveLeft = computeDirToMove(-camera.right());
      auto expectedEyeLeft = camera.eye() + dirToMoveLeft;
      auto expectedCenterLeft = camera.center() + dirToMoveLeft;
      camera.dolly(nbt::graphics::left);
      expect_vec3_near(expectedEyeLeft, camera.eye(), 0.0001);
      expect_vec3_near(expectedCenterLeft, camera.center(), 0.0001f);
    }
  }

  SECTION("shouldStoreNearRange") {
    auto defaultCam = nbt::graphics::Camera();

    CHECK(0.01f == defaultCam.nearRange());
  }

  SECTION("shouldStoreFarRange") {
    auto defaultCam = nbt::graphics::Camera();

    CHECK(2.0f == defaultCam.farRange());
  }
}