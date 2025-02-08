
if(BUILD_TESTING)

  if(MSVC)
    get_scoped_target_list(scoped_targets)

    foreach(target IN LISTS scoped_targets)
      if(TARGET ${target})
        set_target_properties( ${target} PROPERTIES FOLDER "Tests")
      endif()
    endforeach()
  endif()
endif()
