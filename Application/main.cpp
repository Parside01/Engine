#include "engine.hpp"

class Sandbox : public Engine::Application {
public:

};

int main() {
    Sandbox* box = new Sandbox();
    box->Run();
    delete box;
    return 0;
}