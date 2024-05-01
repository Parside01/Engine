cmake_minimum_required(VERSION 3.16)

project(Engine)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CORE_SOURCES)
file(GLOB CORE_SOURCES "${ENGINE_SOURCE_DIR}/core/*.cpp")

set(CORE_HEADERS)
file(GLOB CORE_HEADERS "${ENGINE_SOURCE_DIR}/core/*.h")

set(ENGINE_SOURCES ${CORE_SOURCES} ${CORE_HEADERS})

add_library(Engine SHARED ${ENGINE_SOURCES})

find_package(OpenGL REQUIRED)


add_executable(engine ${ENGINE_SOURCE_DIR}/main.cpp)
target_link_libraries(engine ${OpenGL_LIBRARIES})

install(TARGETS engine DESTINATION lib)