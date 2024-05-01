cmake_minimum_required(VERSION 3.13)

project(Sandbox)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Engine)
set(ENGINE_INCLUDE_DIR ${ENGINE_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)

# Добавляем исходные файлы приложения
add_executable(Sandbox main.cpp)

# Определяем зависимость от Engine
target_link_libraries(Sandbox ${ENGINE_SOURCE_DIR}/build/libEngine.so)

# Устанавливаем исполняемый файл
install(TARGETS Sandbox DESTINATION bin)