// #include "include/engine.hpp"

// #include "include/engine_precompile_headers.hpp"

#include "Engine/engine.hpp"
#include "Engine/engine_precompile_headers.hpp"

int main(int argc, char** argv) {
    std::cout << "ENGINE START" << std::endl;

    Engine::Log::Init();

    EG_CORE_INFO("INIT LOGGER");
    
    auto app = Engine::CreateApplication();
    EG_CORE_INFO("CREATE APPLICATION");
    if (app == nullptr) {
        EG_CORE_ERROR("Failed to create application!");
    }
    app->Run();
    delete app;

    std::cout << "ENGINE STOP" << std::endl;
    return 0;
}
