cmake_minimum_required(VERSION 3.16)

project(Engine)

set(CMAKE_CXX_STANDARD 17)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
set(INCLUDE_DIR usr/include)

message(STATUS ${THIRD_PARTY_DIR})

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

add_library(stb_image
            ${THIRD_PARTY_DIR}/stb_image/stb_image.hpp
            ${THIRD_PARTY_DIR}/stb_image/stb_image.cpp
)

target_include_directories(stb_image PUBLIC ${ENGINE_INCLUDE_DIR})


add_library(entt ${THIRD_PARTY_DIR}/entt/entt.hpp ${THIRD_PARTY_DIR}/entt/entt.cpp)

# --- Ищем нужные пакетики.

find_package(OpenGL REQUIRED)
find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

# --- Ищем нужные пакетики.

# --- Добавляем библиотеку сериализации YAML файлов 

add_subdirectory(${THIRD_PARTY_DIR}/yaml-cpp)
include_directories(${THIRD_PARTY_DIR}/yaml-cpp/include)

# --- Добавляем библиотеку сериализации YAML файлов

# --- ImGuizmo

add_library(imguizmo 
        ${THIRD_PARTY_DIR}/ImGuizmo/ImGuizmo.cpp
        ${THIRD_PARTY_DIR}/ImGuizmo/ImGuizmo.h
)
target_compile_definitions(imguizmo PRIVATE -DIMGUI_DEFINE_MATH_OPERATORS)

target_include_directories(imguizmo PUBLIC ${THIRD_PARTY_DIR}/imgui)
target_include_directories(imguizmo PUBLIC ${GLFW3_INCLUDE_DIR})
target_include_directories(imguizmo PUBLIC ${THIRD_PARTY_DIR}/imgui/ ${THIRD_PARTY_DIR}/imgui/backends/)

# --- ImGuizmo

# --- Все еще пытаюсь добавить imgui сюда.

set(CORE_HEADERS)
file(GLOB_RECURSE CORE_HEADERS "${ENGINE_INCLUDE_DIR}/*.hpp")

set(CORE_SOURCES)
file(GLOB_RECURSE CORE_SOURCES "${ENGINE_SOURCE_DIR}/*.cpp")

set(ENGINE_SOURCES ${CORE_SOURCES} ${CORE_HEADERS}
        include/Engine/Render/Renderer2D.hpp
        src/Render/Renderer2D.cpp)
add_library(Engine SHARED ${ENGINE_SOURCES})
target_link_libraries(Engine PUBLIC imgui stb_image entt ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} yaml-cpp imguizmo)


# --- Добавляем дириктории инклюдов для Engine.

target_include_directories(Engine PUBLIC ${THIRD_PARTY_DIR}/imgui)
target_include_directories(Engine PUBLIC ${GLFW3_INCLUDE_DIR})
target_include_directories(Engine PUBLIC ${THIRD_PARTY_DIR}/ImGuizmo)
target_include_directories(Engine PUBLIC ${THIRD_PARTY_DIR}/imgui/ ${THIRD_PARTY_DIR}/imgui/backends/)
target_include_directories(Engine PUBLIC ${ENGINE_INCLUDE_DIR}/)
target_include_directories(Engine PUBLIC ${THIRD_PARTY_DIR}/stb_image)
target_include_directories(Engine PUBLIC ${THIRD_PARTY_DIR}/entt)

# --- Добавляем дириктории инклюдов для Engine.



add_executable(engine ${ENGINE_SOURCE_DIR}/EntryPoint.cpp)
target_link_libraries(engine ${OPENGL_LIBRARIES} imgui Engine spdlog::spdlog fmt::fmt glfw glm::glm)
link_directories(${OPENGL_gl_LIBRARY})

target_precompile_headers(engine PRIVATE ${ENGINE_INCLUDE_DIR}/Engine/engine_precompile_headers.hpp)
message(STATUS attach ${ENGINE_INCLUDE_DIR}/engine_precompile_headers.hpp)

install(TARGETS engine DESTINATION lib)