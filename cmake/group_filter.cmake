function(group_filter target)
  get_target_property(sources ${target} SOURCES)

  foreach(source IN LISTS sources)
      get_filename_component(source_path ${source} PATH)
      file(RELATIVE_PATH relative_path "${PROJECT_SOURCE_DIR}" ${source_path})
     
      string(FIND ${relative_path} "/" target_position)

      #gets rid of the top-level directory as the group name
      if(NOT target_position EQUAL -1)
          string(SUBSTRING "${relative_path}" "${target_position}" -1 result_path)
      endif()

      source_group("${result_path}" FILES "${source}")

  endforeach()
  
endfunction()