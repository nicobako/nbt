# dir nbt/samples/nbt/glt

# since nbt_glt uses third party libraries, and is dependent on resource files
# such as shaders, we will build a 'custom target' that will allow the user to
# copy all of the required files with one click.

set(nbt_glt_dlls ${nbt_extern_dir}/dll/glew32.dll
    ${nbt_extern_dir}/dll/SDL2.dll)

set(glt_res_files_dir ${nbt_src_dir}/nbt/glt/res)

# since nbt_glt uses many third party libs and has resource files we will go
# ahead and add a custom target to be able to copy those files.
add_custom_target(nbt_glt_copy_files_debug
                  COMMAND ${CMAKE_COMMAND} -E copy ${nbt_glt_dlls}
                          ${samples_output_dir}/Debug
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${glt_res_files_dir} ${samples_output_dir}/Debug/res)

add_custom_target(
  nbt_glt_copy_files_release
  COMMAND ${CMAKE_COMMAND} -E copy ${nbt_glt_dlls} ${samples_output_dir}/Release
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${glt_res_files_dir}
          ${samples_output_dir}/Release/res)

set(nbt_glt_samples window_creation drawing_points)

foreach(nbt_glt_sample ${nbt_glt_samples})
  add_subdirectory(${nbt_glt_sample})
endforeach(nbt_glt_sample)
