cmake_minimum_required(VERSION 3.16)

project(Engine)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ДА КАК ЭТО ФИКИСИТЬ?
# /home/parside/projects/local/engine/third_party
# /home/kneepy/bin/c/Engine/third_party
set(THIRD_PARTY_DIR /home/kneepy/bin/c/Engine/third_party)
set(INCLUDE_DIR usr/include)

message(STATUS ${THIRD_PARTY_DIR})

# --- Все еще пытаюсь добавить imgui сюда.

add_library(imgui 
            ${THIRD_PARTY_DIR}/imgui/imgui.cpp 
            ${THIRD_PARTY_DIR}/imgui/imgui_draw.cpp 
            ${THIRD_PARTY_DIR}/imgui/imgui_tables.cpp 
            ${THIRD_PARTY_DIR}/imgui/imgui_widgets.cpp
            ${THIRD_PARTY_DIR}/imgui/imgui_demo.cpp
            
            ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_glfw.cpp 
            ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

target_include_directories(imgui PUBLIC ${THIRD_PARTY_DIR}/imgui)
target_include_directories(imgui PUBLIC ${GLFW3_INCLUDE_DIR})
target_include_directories(imgui PUBLIC ${THIRD_PARTY_DIR}/imgui/ ${THIRD_PARTY_DIR}/imgui/backends/)

target_link_libraries(Engine PUBLIC imgui)
# --- Все еще пытаюсь добавить imgui сюда.

set(CORE_SOURCES)
file(GLOB_RECURSE CORE_SOURCES "${ENGINE_SOURCE_DIR}/*.cpp")

set(CORE_HEADERS)
file(GLOB_RECURSE CORE_HEADERS "${ENGINE_INCLUDE_DIR}/*.hpp")

set(ENGINE_SOURCES ${CORE_SOURCES} ${CORE_HEADERS})
add_library(Engine SHARED ${ENGINE_SOURCES})



# --- Добавляем дириктории инклюдов для Engine.

target_include_directories(Engine PUBLIC ${THIRD_PARTY_DIR}/imgui)
target_include_directories(Engine PUBLIC ${GLFW3_INCLUDE_DIR})
target_include_directories(Engine PUBLIC ${THIRD_PARTY_DIR}/imgui/ ${THIRD_PARTY_DIR}/imgui/backends/)
target_include_directories(Engine PUBLIC ${ENGINE_INCLUDE_DIR}/)


# --- Добавляем дириктории инклюдов для Engine.



find_package(OpenGL REQUIRED)
find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(glm REQUIRED)

add_executable(engine ${ENGINE_SOURCE_DIR}/EntryPoint.cpp)
target_link_libraries(engine ${OpenGL_LIBRARIES} imgui Engine spdlog::spdlog fmt::fmt glfw glm::glm)

target_precompile_headers(engine PRIVATE ${ENGINE_INCLUDE_DIR}/Engine/engine_precompile_headers.hpp)
message(STATUS attach ${ENGINE_INCLUDE_DIR}/engine_precompile_headers.hpp)

install(TARGETS engine DESTINATION lib)