cmake_minimum_required(VERSION 3.13)

project(Sandbox)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/src)
set(ENGINE_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/build)
set(ENGINE_INCLUDE_DIR ${ENGINE_SOURCE_DIR})

find_package(OpenGL REQUIRED)


include_directories(${ENGINE_INCLUDE_DIR})

# Добавляем исходные файлы приложения
add_executable(Sandbox main.cpp)
# Определяем зависимость от Engine
target_link_libraries(Sandbox ${ENGINE_BUILD_DIR}/libEngine.so)


# target_link_libraries(Sandbox Engine)

# Устанавливаем исполняемый файл
install(TARGETS Sandbox DESTINATION bin)