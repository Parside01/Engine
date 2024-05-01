cmake_minimum_required(VERSION 3.16)

project(Engine)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ENGINE_INCLUDE_DIR ${ENGINE_SOURCE_DIR}/include)

set(CORE_SOURCES)
file(GLOB_RECURSE CORE_SOURCES "${ENGINE_SOURCE_DIR}/*.cpp")
#file(GLOB CORE_SOURCES "${ENGINE_SOURCE_DIR}/*.cpp")
message(STATUS ${CORE_SOURCES})

set(CORE_HEADERS)
file(GLOB_RECURSE CORE_HEADERS "${ENGINE_INCLUDE_DIR}/*.hpp")
message(STATUS ${CORE_HEADERS})

set(ENGINE_SOURCES ${CORE_SOURCES} ${CORE_HEADERS})

add_library(Engine SHARED ${ENGINE_SOURCES})

find_package(OpenGL REQUIRED)

message(STATUS ${ENGINE})

add_executable(engine ${ENGINE_SOURCE_DIR}/main.cpp)
target_link_libraries(Engine ${OpenGL_LIBRARIES})

install(TARGETS Engine DESTINATION lib)