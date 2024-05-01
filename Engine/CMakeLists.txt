cmake_minimum_required(VERSION 3.12)
project(Engine)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(engine ${SOURCES})

set_target_properties(Engine PROPERTIES
    OUTPUT_NAME Engine
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

find_package(OpenGL REQUIRED)
target_link_libraries(Engine PRIVATE OpenGL::GL)

install(TARGETS Engine
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
)

install(DIRECTORY src/
    DESTINATION include/Engine
    FILES_MATCHING PATTERN "*.h"
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

# Install the library and header files
install()
