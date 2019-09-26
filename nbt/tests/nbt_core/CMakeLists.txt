# dir nbt/tests/nbt_core

add_executable(nbt_core_tests
               main.cpp
               RandomTests.cpp
               ValueRangeTests.cpp
               NamedTypeTests.cpp
               ErrorTests.cpp
               MathTests.cpp)

target_link_libraries(nbt_core_tests PRIVATE catch2 nbt_core)

add_test(NAME nbt_core_tests COMMAND nbt_core_tests)
