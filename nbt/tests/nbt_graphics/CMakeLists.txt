# dir nbt/tests/nbt/graphics

set(test_name nbt_graphics_tests)

add_executable(nbt_graphics_tests
               main.cpp
               gltTests.hpp
               WindowMock.hpp
               WindowTests.cpp
               ShaderMock.hpp
               ShaderTests.cpp
               ProgramMock.hpp
               ProgramTests.cpp
               CameraTests.cpp)

target_link_libraries(nbt_graphics_tests PRIVATE catch2 nbt_graphics)

set(nbt_graphics_dlls ${nbt_extern_dir}/dll/glew32.dll)

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET nbt_graphics_tests POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${nbt_graphics_dlls}
                           ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/)

add_test(NAME nbt_graphics_tests COMMAND nbt_graphics_tests)
