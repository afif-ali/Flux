#include "Engine.h"

int main()
{
    Engine::Initialize(800, 600, "Flux");
    Engine::Run();
    Engine::Shutdown();

    return 0;
}