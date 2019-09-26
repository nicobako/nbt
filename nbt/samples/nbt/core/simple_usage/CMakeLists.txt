# dir nbt/samples/core/simple_usage

set(sample_prefix sample_nbt_core_)
set(sample_name simple_usage)

add_executable(${sample_prefix}${sample_name} ${sample_name}.cpp)

target_include_directories(${sample_prefix}${sample_name}
                           PUBLIC ${nbt_include_dir})
