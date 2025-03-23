
add_subdirectory(glm)
add_subdirectory(stb)

FetchContent_Declare(
  SDL
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG        release-3.2.2 # release-1.10.0
)

FetchContent_MakeAvailable(SDL)

# get_scoped_target_list(scoped_targets)

# if(MSVC OR XCODE)
#   foreach(target IN LISTS scoped_targets)
#     if(TARGET ${target})
      
#       set(folder_tree "Deps")
#       get_target_property(folder ${target} FOLDER)

#       if(folder)
#         set(folder_tree "${folder_tree}/${folder}")
#       endif()
      
#       set_target_properties(${target} PROPERTIES 
#         FOLDER "${folder_tree}"
#         RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>" )

#     endif()
#   endforeach()
# endif()
