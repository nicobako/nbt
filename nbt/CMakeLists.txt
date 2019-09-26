# directory /nbt (nbt_root_dir)

cmake_minimum_required(VERSION 3.8)

# Name of project = nbt (Nico Bako Tools)
project(nbt VERSION 0.3 LANGUAGES CXX)

set(${CMAKE_CONFIGURATION_TYPES} Debug Release)

set(nbt_root_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(nbt_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(nbt_samples_dir ${CMAKE_CURRENT_SOURCE_DIR}/samples)
set(nbt_extern_dir ${CMAKE_CURRENT_SOURCE_DIR}/extern)
set(nbt_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(nbt_tests_dir ${CMAKE_CURRENT_SOURCE_DIR}/tests)

set(OpenGL_GL_PREFERENCE GLVND)
link_directories(${nbt_extern_dir}/lib)

if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX _d)
endif()

# first we build the library itself
add_subdirectory(${nbt_src_dir})

# then we build the tests
option(build_tests "to build the test you must have GoogleTest" ON)
if(${build_tests})
  add_subdirectory(${nbt_tests_dir})
endif()

# then we build the samples
option(build_samples "build the samples" ON)
if(${build_samples})
  add_subdirectory(${nbt_samples_dir})
endif()
