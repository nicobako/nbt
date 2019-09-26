# this cmake script generates doxygen documentation for all folders listed in
# the variable ${doc_dirs} In each folder there must be a `docs` folder
# containing a `Doxyfile.in`, which will be configured.

set(doxypypy_filter "")
find_program(doxypypy_exe doxypypy)
if(doxypypy_exe)
  message(STATUS "doxypypy = ${doxypypy_exe}")
  set(doxypypy_filter "*.py=\"${doxypypy_exe} -a -c\"")
  message(STATUS "doxypypy_filter = ${doxypypy_filter}")
endif()

find_program(chrome_exe chrome "C:/Program Files (x86)/Google/Chrome/Application")
message(STATUS "chrome browser: ${chrome_exe}")

find_package(Doxygen)

if(DOXYGEN_FOUND)

  # paths are relative to ${CMAKE_SOURCE_DIR}
  set(doc_dirs nbt)

  foreach(doc_dir IN LISTS doc_dirs)

    message(STATUS "documentation will be built for : ${doc_dir}")

    # get path to doxyfile
    set(doc_dir_abs_path ${CMAKE_SOURCE_DIR}/${doc_dir}/docs)

    # find the doxyfile that still needs to be configured
    set(doxyfile_to_configure ${doc_dir_abs_path}/Doxyfile.in)

    # configure the doxyfile
    set(output_dir ${CMAKE_BINARY_DIR}/docs/${doc_dir})
    configure_file(${doxyfile_to_configure} ${output_dir}/Doxyfile)

    # create the custom target replace any slashes with underscores
    string(REPLACE "/"
                   "_"
                   docs_target_name
                   "docs_${doc_dir}")

    add_custom_target(${docs_target_name}
	                  COMMAND ${DOXYGEN_EXECUTABLE} ${output_dir}/Doxyfile
					  COMMAND ${chrome_exe} ${output_dir}/html/index.html
                      WORKING_DIRECTORY ${output_dir}
                      COMMENT "Generating Doxygen documentation for ${doc_dir}"
                      VERBATIM
                      SOURCES ${doxyfile_to_configure} ${CMAKE_CURRENT_LIST_FILE})

    if(NOT TARGET ${docs_target_name})
      message(FATAL_ERROR "target failed to be created ${docs_target_name}")
    endif()

    # after you build the documentation, wouldn't it be nice if it automatically
    # opened in your browser...
    add_custom_command(TARGET ${docs_target_name} POST_BUILD
                       COMMAND chrome ${output_dir}/html/index.html)

    # special function that puts a target into a a folder (for visual studio)
    put_target_in_folder(${docs_target_name} docs)
  endforeach()

endif()
