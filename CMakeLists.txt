cmake_minimum_required(VERSION 3.14..3.24)

project( MyProject 
  VERSION 0.0.0
  DESCRIPTION "The Template Project"
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

include(CTest)
include(FetchContent)

include(cmake/group_filter.cmake)

add_subdirectory(3rd-party)
add_subdirectory(app)     # set a desirable name
add_subdirectory(library) # set a desirable name
add_subdirectory(tools)
add_subdirectory(tests)

