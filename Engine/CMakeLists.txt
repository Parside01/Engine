cmake_minimum_required(VERSION 3.16)

project(Engine)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ENGINE_INCLUDE_DIR ${ENGINE_SOURCE_DIR}/include)
set(THIRD_PARTY_DIR /home/kneepy/bin/c/Engine/third_party)

message(STATUS ${THIRD_PARTY_DIR})

# --- Все еще пытаюсь добавить imgui сюда.

add_library(imgui 
            ../third_party/imgui/imgui.cpp 
            ../third_party/imgui/imgui_draw.cpp 
            ../third_party/imgui/imgui_tables.cpp 
            ../third_party/imgui/imgui_widgets.cpp
            
            ../third_party/imgui/backends/imgui_impl_glfw.cpp 
            ../third_party/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC ${THIRD_PARTY_DIR}/imgui)
target_include_directories(imgui PUBLIC ${GLFW3_INCLUDE_DIR})
target_include_directories(imgui PUBLIC ${THIRD_PARTY_DIR}/imgui/ ${THIRD_PARTY_DIR}/imgui/backends/)

# --- Все еще пытаюсь добавить imgui сюда.

set(CORE_SOURCES)
file(GLOB_RECURSE CORE_SOURCES "${ENGINE_SOURCE_DIR}/*.cpp")

set(CORE_HEADERS)
file(GLOB_RECURSE CORE_HEADERS "${ENGINE_INCLUDE_DIR}/*.hpp")

set(ENGINE_SOURCES ${CORE_SOURCES} ${CORE_HEADERS})
add_library(Engine SHARED ${ENGINE_SOURCES})

find_package(OpenGL REQUIRED)
find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)

add_executable(engine ${ENGINE_SOURCE_DIR}/EntryPoint.cpp)

target_link_libraries(engine ${OpenGL_LIBRARIES} imgui Engine spdlog::spdlog fmt::fmt glfw)

target_precompile_headers(engine PRIVATE ${ENGINE_INCLUDE_DIR}/engine_precompile_headers.hpp)
message(STATUS attach ${ENGINE_INCLUDE_DIR}/engine_precompile_headers.hpp)

install(TARGETS engine DESTINATION lib)