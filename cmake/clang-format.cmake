# Additional targets to perform clang-format/clang-tidy

find_program(clang_format "clang-format")
message(STATUS "clang-format : ${clang_format}")
if(clang_format)

  set(dirs_to_format
      nbt)

  foreach(dir_to_format IN LISTS dirs_to_format)
    message(STATUS "clang-format will be applied to dir : ${dir_to_format}")

    file(GLOB_RECURSE files_to_format
         RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/${dir_to_format}/*.cpp
                  ${CMAKE_SOURCE_DIR}/${dir_to_format}/*.hpp)

    string(REPLACE "/"
                   "_"
                   custom_target_suffix
                   ${dir_to_format})

    add_custom_target(
      clang-format_${custom_target_suffix}
      COMMAND ${clang_format} -style=file -i ${files_to_format}
      SOURCES ${CMAKE_CURRENT_LIST_FILE} ${CMAKE_SOURCE_DIR}/.clang-format
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      COMMENT "applying clang format to files: ${files_to_format}")

    put_target_in_folder(clang-format_${custom_target_suffix} clang_format)

  endforeach()

endif()
