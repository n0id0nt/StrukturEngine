#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again

#include "Core\skGameData.h"
#include "Core\skGame.h"

int main(int argc, char* args[])
{
    Struktur::Core::Game();
    return 0;
}