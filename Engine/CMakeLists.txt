cmake_minimum_required(VERSION 3.16)

project(Engine)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ENGINE_INCLUDE_DIR ${ENGINE_SOURCE_DIR}/include)


set(CORE_SOURCES)
file(GLOB_RECURSE CORE_SOURCES "${ENGINE_SOURCE_DIR}/*.cpp")
message(STATUS All cpp files --- ${CORE_SOURCES})

set(CORE_HEADERS)
file(GLOB_RECURSE CORE_HEADERS "${ENGINE_INCLUDE_DIR}/*.hpp")
message(STATUS All hpp files --- ${CORE_HEADERS})

set(ENGINE_SOURCES ${CORE_SOURCES})

add_library(Engine SHARED ${ENGINE_SOURCES})

find_package(OpenGL REQUIRED)
find_package(ImGui REQUIRED)
find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(engine ${ENGINE_SOURCE_DIR}/EntryPoint.cpp)
target_link_libraries(engine ${OpenGL_LIBRARIES} Engine spdlog::spdlog fmt::fmt glfw)

target_precompile_headers(engine PRIVATE ${ENGINE_INCLUDE_DIR}/engine_precompile_headers.hpp)
message(STATUS attach ${ENGINE_INCLUDE_DIR}/engine_precompile_headers.hpp)

install(TARGETS engine DESTINATION lib)