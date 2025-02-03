add_library(library)

file(GLOB_RECURSE SOURCES src/**.cpp)
file(GLOB_RECURSE HEADERS include/**.h include/**.hpp include/**.inl)

target_include_directories(library PUBLIC include)

target_sources(library PRIVATE ${HEADERS} PRIVATE ${SOURCES})

set_target_properties(library PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>"
  ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>")

if(MSVC)
  group_filter(library)
endif(MSVC)