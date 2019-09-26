cmake_minimum_required(VERSION 3.15)

project(nbt)

# version numbers
set(nbt_VERSION ${version_from_file}
    CACHE STRING "the version of the monorepo"
    FORCE)



# Get the git description of the current commit
execute_process(COMMAND git describe
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE GIT_DESCRIPTION
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get the date-time
string(TIMESTAMP date_time "%Y-%m-%d-%H-%M-%S")

# installation location
set(root_install_dir nbt_install
    CACHE PATH "the root installation location")

set(
  final_install_dir
  ${root_install_dir}/${GIT_DESCRIPTION}_${nbt_VERSION}${nbt_VERSION_SUFFIX}
  )

message(STATUS "installation directory: ${final_install_dir}")

# cmake installation variables
set(CMAKE_INSTALL_PREFIX ${final_install_dir})
set(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_DOCIR ${CMAKE_INSTALL_PREFIX}/doc)
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(CMAKE_DEBUG_POSTFIX _d)

# we want to generate the compile commands this only happens if the build system
# supports it
set(CMAKE_EXPORT_COMPILE_COMMANDS ON
    CACHE BOOL "We want to export the compile commands"
    FORCE)

# we want to separate projects into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# cmake installation option
include(InstallRequiredSystemLibraries)

# enable testing
enable_testing()

# we create a simple function for putting a target in a folder
include(cmake/put_target_in_folder.cmake)

# add the clang-format tool
include(cmake/clang-format.cmake)

# to run the cmake-format tool on all CMakeLists.txt in this project
# type this into a terminal
# > cmake -P cmake/cmake-format.cmake

# build the doxygen documentation
include(cmake/doxygen-docs.cmake)

# build third party libraries
add_subdirectory(third_party)

# build nbt
add_subdirectory(nbt)

install(CODE "execute_process(COMMAND git archive -o ${final_install_dir}/src.zip HEAD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})")
