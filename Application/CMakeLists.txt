cmake_minimum_required(VERSION 3.13)

project(Sandbox)

set(ENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Engine)
set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/src)
set(ENGINE_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/build)
set(ENGINE_INCLUDE_DIR ${ENGINE_DIR}/include)

find_package(OpenGL REQUIRED)
find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)

add_library(lib
        Layer2D.cpp
        Layer2D.hpp)

include_directories(${ENGINE_INCLUDE_DIR})
include_directories(${ENGINE_DIR}/third_party)
include_directories(${ENGINE_DIR}/third_party/entt)

# Добавляем исходные файлы приложения
add_executable(Sandbox main.cpp)
target_link_libraries(Sandbox ${ENGINE_BUILD_DIR}/libEngine.so OpenGL::GL fmt::fmt glfw lib)


# target_link_libraries(Sandbox Engine)

# Устанавливаем исполняемый файл
install(TARGETS Sandbox DESTINATION bin)


add_custom_command(
        TARGET Sandbox
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
