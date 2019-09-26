# dir nbt/tests/nbt_ascii

add_executable(nbt_ascii_tests
               main.cpp
               AsciiTests.hpp
               ConversionsTests.cpp
               RegexTests.cpp
               FileReaderTests.cpp
               FileWriterTests.cpp)

# copy the resource files
add_custom_command(TARGET nbt_ascii_tests PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${CMAKE_CURRENT_SOURCE_DIR}/res
                           ${CMAKE_CURRENT_BINARY_DIR}/res)

target_link_libraries(nbt_ascii_tests PRIVATE catch2 nbt_ascii)

add_test(NAME nbt_ascii_tests COMMAND nbt_ascii_tests)
