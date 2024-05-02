#ifndef ENGINE_ENTRYPOINT_HPP 
#define ENGINE_ENTRYPOINT_HPP

#include "../include/Application.hpp"
#include "../include/Core.hpp"

#ifdef __linux__

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv);

#else

    #error "Unsupported platform"

#endif

#endif