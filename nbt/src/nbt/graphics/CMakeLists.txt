# dir src/nbt/graphics

add_library(nbt_graphics_components STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp)

target_sources(nbt_graphics_components
               PRIVATE
               ${nbt_include_dir}/nbt/graphics/Camera.hpp
               ${nbt_include_dir}/nbt/graphics/Direction.hpp)

target_link_libraries(nbt_graphics_components PUBLIC nbt_core)

put_target_in_folder(nbt_graphics_components nbt/graphics)

# this is so we can link to glew... I really need to figure out a way to avoid
# calling 'link_directories'
link_directories(${nbt_extern_dir}/lib)

add_library(nbt_graphics
            ${nbt_lib_type}
            ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/GlfwWindow.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Program.cpp)

target_sources(nbt_graphics
               PRIVATE
               ${nbt_include_dir}/nbt/graphics.hpp
               ${nbt_include_dir}/nbt/graphics/Window.hpp
               ${nbt_include_dir}/nbt/graphics/GlfwWindow.hpp
               ${nbt_include_dir}/nbt/graphics/Shader.hpp
               ${nbt_include_dir}/nbt/graphics/Program.hpp)

target_include_directories(nbt_graphics
                           PUBLIC ${nbt_include_dir} ${nbt_extern_dir}/include
                                  ${nbt_extern_dir}/glm)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

if(WIN32)
  target_link_libraries(nbt_graphics
                        PUBLIC nbt_core
                               nbt_graphics_components
                               ${OPENGL_gl_LIBRARY}
                               glew32
                               glfw)
endif()

if(UNIX)
  target_link_libraries(nbt_graphics
                        PUBLIC nbt_core
                               nbt_graphics_components
                               ${OPENGL_opengl_LIBRARY}
                               ${OPENGL_glx_LIBRARY}
                               GLEW
                               glfw
                        INTERFACE GLU
                                  X11
                                  dl
                                  pthread
                                  Xxf86vm
                                  pthread
                                  Xrandr
                                  Xinerama
                                  Xi
                                  Xcursor)
endif()
