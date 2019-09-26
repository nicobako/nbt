// This example shows how to create a simple SDL SdlWindow for 3D visualization

#include <iostream>
#include <string>

#include <nbt/glt/SdlWindow.hpp>

void drawTriangle();

int main(int argc, char * argv[]) {
  // Create the SdlWindow.
  nbt::glt::SdlWindow sdlWindow("Sample - creating a window", 800, 800);

  // Don't forget that you also have access to a terminal,
  // so you can print stuff to it!
  std::cout << "Name of window: " << sdlWindow.getTitle() << std::endl;

  // Create the while loop that will persist until the
  // window is closed.
  while (!sdlWindow.isClosed()) {
    // You must call thin functio before/after every
    // draw call.
    sdlWindow.update();

    // We are only doing this draw for visual effect.
    // Drawing directly with OpenGL only works if you
    // don't create a Scene object and don't pass it to
    // the Window
    drawTriangle();
  }

  return 0;
}

void drawTriangle() {
  // In this example we are drawing directly using OpenGL,
  // but this is not recommended!!!
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.5f, -0.5f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.5f, 0.0f);
  glEnd();
}