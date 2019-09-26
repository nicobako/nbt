# dir nbt/src/nbt/ascii

add_library(nbt_ascii
            ${nbt_lib_type}
            ${nbt_src_dir}/nbt/ascii/Conversions.cpp
            ${nbt_src_dir}/nbt/ascii/Regex.cpp
            ${nbt_src_dir}/nbt/ascii/FileReader.cpp
            ${nbt_src_dir}/nbt/ascii/FileWriter.cpp)

target_sources(nbt_ascii
               PRIVATE
               ${nbt_include_dir}/nbt/ascii.hpp
               ${nbt_include_dir}/nbt/ascii/Conversions.hpp
               ${nbt_include_dir}/nbt/ascii/FileReader.hpp
               ${nbt_include_dir}/nbt/ascii/FileWriter.hpp
               ${nbt_include_dir}/nbt/ascii/Regex.hpp)

target_include_directories(nbt_ascii PUBLIC ${nbt_include_dir})

target_link_libraries(nbt_ascii PUBLIC nbt_core)
