# dir nbt/samples/nbt/glt/simple_usage

set(sample_prefix sample_nbt_glt)
set(sample_name ${nbt_glt_sample})

set(sample_exe_name ${sample_prefix}_${sample_name})

add_executable(${sample_exe_name} ${sample_name}.cpp)

target_include_directories(${sample_exe_name}
                           PUBLIC ${nbt_include_dir} ${nbt_extern_dir}/include)

find_package(OpenGL REQUIRED)

target_link_libraries(${sample_exe_name}
                      ${OPENGL_gl_LIBRARY}
                      ${nbt_extern_dir}/lib/glew32.lib
                      ${nbt_extern_dir}/lib/SDL2.lib
                      ${nbt_extern_dir}/lib/SDL2main.lib
                      nbt_glt)

add_dependencies(${sample_exe_name} nbt_glt)
