# directory nbt/tests

set(nbt_tests nbt_core nbt_config nbt_binary nbt_ascii nbt_graphics)

foreach(nbt_test ${nbt_tests})
  add_subdirectory(${nbt_test})
  put_target_in_folder(${nbt_test}_tests nbt/tests)
endforeach()
