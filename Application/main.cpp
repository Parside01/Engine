#include "include/engine.hpp"

class Sandbox : public Engine::Application {
public:

};

int main() {
    Sandbox* box = new Sandbox();
    Engine::Core *core = new Engine::Core();
    box->Run();
    delete box;
    delete core;
    return 0;
}