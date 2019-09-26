# creates a target that will format all CMakeLists.txt files
find_program(cmake_format "cmake-format")
message(STATUS "cmake-format : ${cmake_format}")
if(cmake_format)
  file(GLOB_RECURSE cmake_files_to_format
                    nbt/CMakeLists.txt)

  foreach(cmake_file IN LISTS cmake_files_to_format)
    message(STATUS "formatting ${cmake_file}")
    execute_process(COMMAND cmake-format -i ${cmake_file})
  endforeach()

endif()
