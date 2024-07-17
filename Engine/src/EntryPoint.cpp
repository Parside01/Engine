// #include "include/engine.hpp"

// #include "include/engine_precompile_headers.hpp"

#include "Engine/engine.hpp"
#include "Engine/engine_precompile_headers.hpp"

int main(int argc, char** argv) {
    Engine::Log::Init();
    
    auto app = Engine::CreateApplication();
    if (app == nullptr) {
        EG_CORE_ERROR("Failed to create application!");
    }

    EG_PROFILE_BEGIN_SESSION("Engine", "Runtime_profile.json");
    app->Run();
    EG_PROFILE_END_SESSION();
    delete app;

    return 0;
}
