# directory /nbt/src/nbt

set(nbt_modules ascii binary config core graphics)

foreach(nbt_module ${nbt_modules})
  add_subdirectory(${nbt_module})
  put_target_in_folder(nbt_${nbt_module} nbt/${nbt_module})
endforeach()
