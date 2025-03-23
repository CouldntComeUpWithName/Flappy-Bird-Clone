add_library(stb STATIC)

set(SOURCES src/stb_image.cpp include/stb_image.h)


target_sources(stb PRIVATE ${SOURCES})
target_include_directories(stb PUBLIC include)

set_target_properties(stb PROPERTIES FOLDER "stb")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})