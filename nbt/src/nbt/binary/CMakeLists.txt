# dir nbt/src/nbt/binary

add_library(nbt_binary
            ${nbt_lib_type}
            ${CMAKE_CURRENT_SOURCE_DIR}/FileReader.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/FileWriter.cpp)

target_sources(nbt_binary
               PRIVATE
               ${nbt_include_dir}/nbt/binary/Bytes.hpp
               ${nbt_include_dir}/nbt/binary/Endianness.hpp
               ${nbt_include_dir}/nbt/binary/FileReader.hpp
               ${nbt_include_dir}/nbt/binary/FileWriter.hpp)

target_include_directories(nbt_binary PUBLIC ${nbt_include_dir})

target_link_libraries(nbt_binary PUBLIC nbt_core)
