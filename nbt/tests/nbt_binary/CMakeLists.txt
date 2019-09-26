# dir nbt/tests/nbt_binary

add_executable(nbt_binary_tests
               main.cpp
               BinaryTests.hpp
               BytesTests.cpp
               FileReaderTests.cpp
               FileWriterTests.cpp)

# copy the resource files
add_custom_command(TARGET nbt_binary_tests PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${CMAKE_CURRENT_SOURCE_DIR}/res
                           ${CMAKE_CURRENT_BINARY_DIR}/res)

target_link_libraries(nbt_binary_tests PRIVATE catch2 nbt_binary)

add_test(NAME nbt_binary_tests COMMAND nbt_binary_tests)
