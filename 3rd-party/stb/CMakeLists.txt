add_library(stb STATIC)
file(GLOB_RECURSE SOURCES src/* include/*)

target_sources(stb PRIVATE ${SOURCES})
target_include_directories(stb PUBLIC include)

group_filter(stb)