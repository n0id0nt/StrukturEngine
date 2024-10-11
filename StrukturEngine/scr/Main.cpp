#define _CRT_SECURE_NO_WARNINGS
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again
#undef _CRT_SECURE_NO_WARNINGS

#include "Core\skGameData.h"
#include "Core\skGame.h"

int main(int argc, char* argv[])
{
    Struktur::Core::Game();
    return 0;
}

int WinMain(int argc, char* argv[])
{
    return main(argc, argv);
}