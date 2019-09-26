# nbt::config

add_library(nbt_config
            ${nbt_lib_type}
            ${nbt_src_dir}/nbt/config/Data.cpp
            ${nbt_src_dir}/nbt/config/Property.cpp
            ${nbt_src_dir}/nbt/config/Section.cpp)

target_sources(nbt_config
               PRIVATE
               ${nbt_include_dir}/nbt/config.hpp
               ${nbt_include_dir}/nbt/config/Data.hpp
               ${nbt_include_dir}/nbt/config/Property.hpp
               ${nbt_include_dir}/nbt/config/Section.hpp)

target_link_libraries(nbt_config PRIVATE nbt_ascii nbt_core)

target_include_directories(nbt_config PUBLIC ${nbt_include_dir})
