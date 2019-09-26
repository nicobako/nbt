# dir nbt/samples/nbt/graphics

# since nbt_graphics uses third party libraries, and is dependent on resource
# files such as shaders, we will build a 'custom target' that will allow the
# user to copy all of the required files with one click.

if(WIN32)
  set(nbt_graphics_dlls ${nbt_extern_dir}/dll/glew32.dll
      # ${nbt_extern_dir}/dll/SDL2.dll
      )

  set(graphics_res_files_dir ${nbt_src_dir}/nbt/graphics/res)

  # since nbt_graphics uses many third party libs and has resource files we will
  # go ahead and add a custom target to be able to copy those files.
  add_custom_target(nbt_graphics_copy_files_debug
                    COMMAND ${CMAKE_COMMAND} -E copy ${nbt_graphics_dlls}
                            ${samples_output_dir}/Debug
                    COMMAND ${CMAKE_COMMAND} -E copy ${nbt_graphics_dlls}
                            ${samples_output_dir}/../tests
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                            ${graphics_res_files_dir}
                            ${samples_output_dir}/Debug/res)

  add_custom_target(nbt_graphics_copy_files_release
                    COMMAND ${CMAKE_COMMAND} -E copy ${nbt_graphics_dlls}
                            ${samples_output_dir}/Release
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                            ${graphics_res_files_dir}
                            ${samples_output_dir}/Release/res)
  put_target_in_folder(nbt_graphics_copy_files_debug nbt/samples/graphics)
  put_target_in_folder(nbt_graphics_copy_files_release nbt/samples/graphics)
endif(WIN32)

set(nbt_graphics_samples window_creation plotting_points)

foreach(nbt_graphics_sample ${nbt_graphics_samples})
  add_subdirectory(${nbt_graphics_sample})
  put_target_in_folder(sample_nbt_graphics_${nbt_graphics_sample}
                       nbt/samples/graphics)
endforeach(nbt_graphics_sample)
