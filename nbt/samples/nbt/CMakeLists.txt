# dir nbt/samples/nbt

# samples should be output to ${NBT_BIN_DIR}/samples

set(samples_output_dir ${nbt_bin_dir}/samples)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${samples_output_dir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${samples_output_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${samples_output_dir})

set(nbt_samples_dirs core graphics)

foreach(sample_dir ${nbt_samples_dirs})
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${sample_dir})
endforeach(sample_dir)
