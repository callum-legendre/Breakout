#include "engine.h"
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[])
{
    Engine* engine = new Engine();

    engine->Run();

    delete engine;
    return 0;
}
