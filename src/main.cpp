#include "engine.h"
#include <SDL3/SDL_main.h>

int main()
{
    Engine* engine = new Engine();

    engine->Run();

    delete engine;
}
