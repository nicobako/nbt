# dir nbt/tests/nbt_config

add_executable(nbt_config_tests
               main.cpp
               DataTests.cpp
               PropertyTests.cpp
               SectionTests.cpp)

# copy the resource files
add_custom_command(TARGET nbt_config_tests PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${CMAKE_CURRENT_SOURCE_DIR}/res
                           ${CMAKE_CURRENT_BINARY_DIR}/res)

target_sources(nbt_config_tests PRIVATE ConfigTests.hpp)

target_link_libraries(nbt_config_tests PRIVATE catch2 nbt_config)
