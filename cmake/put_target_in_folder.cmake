function(put_target_in_folder target_name folder)
  set_target_properties(${target_name} PROPERTIES FOLDER ${folder})
endfunction(put_target_in_folder)
