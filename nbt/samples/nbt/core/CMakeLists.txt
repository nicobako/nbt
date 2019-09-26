# dir nbt/samples/nbt/core

set(nbt_core_samples simple_usage)

foreach(nbt_core_sample ${nbt_core_samples})
  add_subdirectory(${nbt_core_sample})
  put_target_in_folder(sample_nbt_core_${nbt_core_sample} nbt/samples/core)
endforeach(nbt_core_sample)
