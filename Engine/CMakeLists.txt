cmake_minimum_required(VERSION 3.16)

project(Engine)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ENGINE_INCLUDE_DIR ${ENGINE_SOURCE_DIR}/include)
set(ENGINE_THIRD_PARTY /home/kneepy/bin/c/Engine/third_party)

# --- Все еще пытаюсь добавить imgui сюда.

add_library(imgui ../)

# --- Все еще пытаюсь добавить imgui сюда.

set(CORE_SOURCES)
file(GLOB_RECURSE CORE_SOURCES "${ENGINE_SOURCE_DIR}/*.cpp")

set(CORE_HEADERS)
file(GLOB_RECURSE CORE_HEADERS "${ENGINE_INCLUDE_DIR}/*.hpp")

set(THIRD_PARTY_LIBS)
file(GLOB_RECURSE THIRD_PARTY_LIBS "${ENGINE_THIRD_PARTY}/*.o" "${ENGINE_THIRD_PARTY}/*.a" "${ENGINE_THIRD_PARTY}/*.so")
message(STATUS All o files --- ${THIRD_PARTY_LIBS})

include_directories(${ENGINE_INCLUDE_DIR})

set(ENGINE_SOURCES ${CORE_SOURCES} ${THIRD_PARTY_LIBS})
add_library(Engine SHARED ${ENGINE_SOURCES})

find_package(OpenGL REQUIRED)
find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(ImGui REQUIRED)


add_executable(engine ${ENGINE_SOURCE_DIR}/EntryPoint.cpp)
target_link_libraries(engine ${OpenGL_LIBRARIES} Engine spdlog::spdlog fmt::fmt glfw ImGui::imgui)

target_precompile_headers(engine PRIVATE ${ENGINE_INCLUDE_DIR}/engine_precompile_headers.hpp)
message(STATUS attach ${ENGINE_INCLUDE_DIR}/engine_precompile_headers.hpp)

install(TARGETS engine DESTINATION lib)