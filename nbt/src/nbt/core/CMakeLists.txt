# dir nbt/src/nbt/core

add_library(nbt_core ${nbt_lib_type} FileHandler.cpp)

target_sources(nbt_core
               PRIVATE
               ${nbt_include_dir}/nbt/core/Error.hpp
               ${nbt_include_dir}/nbt/core/FileHandler.hpp
               ${nbt_include_dir}/nbt/core/NamedType.hpp
               ${nbt_include_dir}/nbt/core/random.hpp
               ${nbt_include_dir}/nbt/core/ValueRange.hpp
               ${nbt_include_dir}/nbt/core/math.hpp)

target_include_directories(nbt_core PUBLIC ${nbt_include_dir})

target_link_libraries(nbt_core PUBLIC fmt glm)
