#include <algorithm>
#include <iostream>
#include <iterator> // back_inserter

#include <nbt/core.hpp>
#include <nbt/graphics/GlfwWindow.hpp>
#include <nbt/graphics/Program.hpp>
#include <nbt/graphics/Shader.hpp>

#include <glm/glm.hpp>

typedef glm::vec3 Position;
typedef glm::vec3 Color;

struct Point {
  Position position;
  Color color;
  float size;
};

static const char * vertex_shader_source =
    "#version 420\n"
    "\n"
    "layout (location = 0) in vec3 vPos;\n"
    "layout (location = 1) in vec3 vCol;\n"
    "layout (location = 2) in float vSize;\n"
    "\n"
    "uniform mat4 perspectiveMat;\n"
    "uniform mat4 lookAtMat\n;"
    "\n"
    "out vec3 vs_color;\n"
    "void main(void)\n"
    "{\n"
    "   gl_Position = perspectiveMat * lookAtMat * vec4(vPos, 1.0);\n"
    "   gl_PointSize = vSize;\n"
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
  nbt::graphics::GlfwWindow window("Plotting points", 640, 480);

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

  // set up the data you want to plot

  nbt::core::ValueRange<float> xValueRange(-5.0f, 5.0f);
  auto xValues = nbt::core::slice(xValueRange, 0.01f);

  std::vector<Point> points;

  auto createPoint = [](float value) -> Point {
    Point point;
    point.position.x = glm::cos(value * 3.14f * 2.0f);
    point.position.y = glm::sin(value * 3.14f * 2.0f);
    point.position.z = value;
    point.color =
        glm::vec3(point.position.x, point.position.y, point.position.z);
    point.size = std::fabs(value) * 5.0f + 1;

    return point;
  };

  std::transform(
      xValues.begin(), xValues.end(), std::back_inserter(points), createPoint);

  // Set up OpenGL stuff to send data to gpu
  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(Point) * points.size(),
      &points[0],
      GL_STATIC_DRAW);

  GLint vPos_location = glGetAttribLocation(program.getId(), "vPos");
  glEnableVertexAttribArray(vPos_location);
  glVertexAttribPointer(
      vPos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void *)0);
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
      sizeof(Point),
      (void *)(sizeof(Position)));
  //// or...
  // glEnableVertexAttribArray(1);
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
  // (void*)(sizeof(float) * 2));

  GLint vSize_location = glGetAttribLocation(program.getId(), "vSize");
  glEnableVertexAttribArray(vSize_location);
  glVertexAttribPointer(
      vSize_location,
      1,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Point),
      (void *)(sizeof(Position) + sizeof(Color)));

  // create a list of indices
  auto indicesRange =
      nbt::core::ValueRange<unsigned>((unsigned)0, points.size() - 1);

  auto indices = nbt::core::slice(indicesRange, (unsigned)1);

  GLuint index_buffer;
  glGenBuffers(1, &index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(
      GL_ELEMENT_ARRAY_BUFFER,
      points.size() * sizeof(unsigned),
      &indices[0],
      GL_STATIC_DRAW);

  window.enable(GL_PROGRAM_POINT_SIZE);
  window.enable(GL_DEPTH_TEST);

  auto camera = nbt::graphics::Camera(
      glm::vec3(0.0, 0.0, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));

  // loop for window
  while (!window.isClosed()) {
    window.drawBackground();
    window.pollEvents(camera);

    program.use();
    program.updateUniform("perspectiveMat", camera.perspectiveMatrix());
    program.updateUniform("lookAtMat", camera.lookAtMatrix());

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glDrawElements(GL_POINTS, points.size() * 4, GL_UNSIGNED_INT, NULL);

    window.swapBuffers();
    window.clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  }

  return 0;
}