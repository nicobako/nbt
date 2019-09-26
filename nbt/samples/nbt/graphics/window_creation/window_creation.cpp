#include <iostream>

#include <nbt/graphics/GlfwWindow.hpp>
#include <nbt/graphics/Program.hpp>
#include <nbt/graphics/Shader.hpp>

#include <glm/glm.hpp>
static void
key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

typedef glm::vec2 Position;
typedef glm::vec3 Color;
static const struct Vertex {
  Position position;
  Color color;
} vertices[3] = {{Position(-0.5f, -0.5), Color(1.0f, 0.0f, 0.0f)},
                 {Position(0.5f, -0.5), Color(0.0f, 1.0f, 0.0f)},
                 {Position(0.0f, 0.5), Color(0.0f, 0.0f, 1.0f)}};

static const char * vertex_shader_source =
    "#version 420\n"
    "\n"
    "layout (location = 0) in vec2 vPos;\n"
    "layout (location = 1) in vec3 vCol;\n"
    "\n"
    "uniform mat4 mvpMat;"
    "\n"
    "out vec3 vs_color;\n"
    "void main(void)\n"
    "{\n"
    "	gl_Position = mvpMat * vec4(vPos, 1.0, 1.0);\n"
    "   vs_color = vCol;\n"
    "}\n";

static const char * fragment_shader_source = "#version 420\n"
                                             "\n"
                                             "in vec3 vs_color;\n"
                                             "out vec4 color;\n"
                                             "void main(void)\n"
                                             "{\n"
                                             "	color = vec4(vs_color, 1.0);\n"
                                             "}\n";

int main(int argc, char * argv[]) {
  // Create the window
  auto window = nbt::graphics::GlfwWindow("My first window", 640, 480);

  // Make sure it was initialized correctly
  if (!window.isInitialized())
    return -1;

  // Create the vertex shader
  nbt::graphics::Shader vertexShader(nbt::graphics::vertex);
  vertexShader.setSource(vertex_shader_source);
  vertexShader.sendToGpu();
  // Check compilation status
  if (!vertexShader.sentToGpu())
    std::cerr << "vert shader error: " << vertexShader.getErrorMessage()
              << std::endl;

  // Create the fragment shader
  nbt::graphics::Shader fragmentShader(nbt::graphics::fragment);
  fragmentShader.setSource(fragment_shader_source);
  fragmentShader.sendToGpu();
  if (!fragmentShader.sentToGpu())
    std::cerr << "frag shader error: " << fragmentShader.getErrorMessage()
              << std::endl;

  // Create the program
  nbt::graphics::Program program;
  program.attach(vertexShader);
  program.attach(fragmentShader);
  program.sendToGpu();

  if (!program.sentToGpu()) {
    std::cerr << program.getErrorMessage() << std::endl;
  }

  // Set up OpenGL stuff to send data to gpu
  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLint vPos_location = glGetAttribLocation(program.getId(), "vPos");
  glEnableVertexAttribArray(vPos_location);
  glVertexAttribPointer(
      vPos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  //// or...
  // glEnableVertexAttribArray(0);
  // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
  // (void*)0);

  GLint vCol_location = glGetAttribLocation(program.getId(), "vCol");
  glEnableVertexAttribArray(vCol_location);
  glVertexAttribPointer(
      vCol_location,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (void *)(sizeof(Position)));
  //// or...
  // glEnableVertexAttribArray(1);
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
  // (void*)(sizeof(float) * 2));

  auto camera = nbt::graphics::Camera();

  // loop for window
  while (!window.isClosed()) {
    window.setBackgroundColor(
        window.getBackgroundColor() - glm::vec3(0.001f, 0.0f, 0.0f));

    window.drawBackground();

    window.pollEvents(camera);

    program.use();
    program.updateUniform("mvpMat", camera.lookAtMatrix());
    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.swapBuffers();
  }

  return 0;
}
