// This sample shows how to draw points using a nbt::glt::StaticScene object

#include <iostream>
#include <string>

#include <nbt/glt/SdlWindow.hpp>
#include <nbt/glt/StaticScene.hpp>

int main(int argc, char * argv[]) {
  // Create the SdlWindow.
  nbt::glt::SdlWindow window("Sample - creating a window", 800, 800);

  // Don't forget that you also have access to a terminal,
  // so you can print stuff to it!
  std::cout << "Name of window: " << window.getTitle() << std::endl;

  // Create the StaticScene object.
  // NOTE - A scene MUST be created after a window.
  //        This is due to intricacies in how an OpenGL contexis created.
  // NOTE - *StaticScenes are *static* because once you add an
  //         object to it you can't manipulate it, and once you send the
  //         scene's data to the GPU you can't add more things to the scene.
  std::shared_ptr<nbt::glt::StaticScene> scene(new nbt::glt::StaticScene());

  // Add the scene to the window
  // window.addScene(scene);

  // Add points to the scene
  nbt::glt::Point point1(
      nbt::glt::Vertex(
          glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
      5.0f);

  // We add the point to the scene
  scene->add(point1);

  nbt::glt::Point point2(
      nbt::glt::Vertex(
          glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
      5.0f);

  scene->add(point2);

  // When you are done adding points to the scene
  // send the data to the GPU.
  // scene->sendToGpu();
  // nbt::glt::Point point3(
  //	nbt::glt::Vertex(
  //		glm::vec3(1.0f, 1.0f, -1.0f),
  //		glm::vec3(0.0f, 0.0f, 1.0f)), 5.0f);
  //
  // std::shared_ptr<nbt::glt::StaticScene> scene2(new nbt::glt::StaticScene()
  // ); window.addScene(scene2); scene2->add(point3); scene2->sendToGpu();

  // Create the while loop that will persist until the
  // window is closed.
  while (!window.isClosed()) {

    // You must call thin functio before/after every
    // draw call.
    window.update();

    scene->draw();
    // Since we passed the scene to a window we ask the
    // window to draw the scene.
    // window.drawScenes();
  }

  return 0;
}