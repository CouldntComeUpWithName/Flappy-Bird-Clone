cmake_minimum_required(VERSION 3.24)

project( Flappy 
  VERSION 0.0.1
  DESCRIPTION "Flappy-Bird-Clone"
  LANGUAGES CXX C )

set(CMAKE_CXX_STANDARD 20) # not recommended, but who cares.
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

include(FetchContent)
include(CTest)

include(cmake/utils.cmake)

add_subdirectory(flappy-game)
add_subdirectory(3rd-party)
add_subdirectory(tools)
add_subdirectory(tests)

if(MSVC)
  
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

  add_definitions("/MP")
  add_definitions("/Zi")

  get_target_list_from(third_party_targets "3rd-party")
  get_target_list_from(test_targets "tests")
  get_target_list_from(tools_targets "tools")
  
  foreach(target IN LISTS third_party_targets)
    if(TARGET ${target})
      
      set(folder_tree "Deps")
      get_target_property(folder ${target} FOLDER)

      if(folder)
        set(folder_tree "${folder_tree}/${folder}")
      endif()
      
      set_target_properties(${target} PROPERTIES 
        FOLDER "${folder_tree}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>" )

    endif()
  endforeach()

  foreach(target IN LISTS test_targets)
    if(TARGET ${target})
      
      set(folder_tree "Tests")
      get_target_property(folder ${target} FOLDER)

      if(folder)
        set(folder_tree "${folder_tree}/${folder}")
      endif()
      
      set_target_properties(${target} PROPERTIES 
        FOLDER "${folder_tree}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/" )

    endif()
  endforeach()

  foreach(target IN LISTS tools_targets)
    if(TARGET ${target})
      
      set(folder_tree "Tools")
      get_target_property(folder ${target} FOLDER)

      if(folder)
        set(folder_tree "${folder_tree}/${folder}")
      endif()
      
      set_target_properties(${target} PROPERTIES 
        FOLDER "${folder_tree}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tools/$<CONFIG>")

    endif()
  endforeach()

endif()