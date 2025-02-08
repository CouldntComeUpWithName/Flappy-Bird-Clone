cmake_minimum_required(VERSION 3.24)

project( Flappy 
  VERSION 0.0.1
  DESCRIPTION "Flappy Bird Clone"
  LANGUAGES CXX C )

set(CMAKE_CXX_STANDARD 20) # not recommended, but who cares.
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

if(MSVC)
  add_definitions("/MP")
  add_definitions("/Zi")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG")
  set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /DEBUG")
endif()

include(FetchContent)
include(CTest)

include(cmake/group_filter.cmake)
include(cmake/utils.cmake)

add_subdirectory(3rd-party)
add_subdirectory(flappy-game)
add_subdirectory(tools)
add_subdirectory(tests)

