#include "skGame.h"
#include "raylib.h"
#include "raymath.h"
#include "skGameData.h"
#include <string>
#include "..\Util\skTask.h"
#include "../ECS/Component/skTransformComponent.h"
#include "../ECS/Component/skPlayerComponent.h"
#include "../ECS/System/skRenderSystem.h"
#include "../ECS/System/skPlayerSystem.h"

void LoadData(Struktur::Core::skGameData* gameData)
{
    for (auto i = 0u; i < 10u; ++i) {
        const auto entity = gameData->registry.create();
        if (i == 0)
        {
            gameData->registry.emplace<Struktur::Component::skPlayerComponent>(entity);
        }
        Transform transform{ {i * 10.f, i * 10.f,0.f},{0.f,0.f,0.f,0.f},{0.f,0.f,0.f} };
        gameData->registry.emplace<Struktur::Component::skTransformComponent>(entity, transform);
    }
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(5s);
}

bool SplashScreen(const double startTime)
{
    //fade in time
    const double fadeInTime = 1.5;
    const double holdTime = 1;
    const double fadeOutTime = 1.5;
    const double currentTime = GetTime();
    if (currentTime > startTime + fadeInTime + holdTime + fadeOutTime)
    {
        return false;
    }

    double textAlpha = 255;
    // Fade in
    if (currentTime < startTime + fadeInTime)
    {
        float t = (currentTime - startTime) / fadeInTime;
        textAlpha *= Lerp(0.f, 1.f, t);
    }
    else if (currentTime > startTime + fadeInTime + holdTime && currentTime < startTime + fadeInTime + holdTime + fadeOutTime)
    {
        float t = (currentTime - startTime - fadeInTime - holdTime) / fadeOutTime;
        textAlpha *= Lerp(1.f, 0.f, t);
    }

    std::string spashScreenName = "Struktur Engine";
    int fontSize = 60;
    int fontWidth = MeasureText(spashScreenName.c_str(), fontSize);
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    BeginDrawing();
    ClearBackground(Color{ 0,0,0,255 });
    DrawText(spashScreenName.c_str(), (width - fontWidth) / 2.f, (height - fontSize) / 2.f, fontSize, Color{ 255,255,255,(unsigned char)textAlpha });
    EndDrawing();
    return true;
}

bool LoadingScreen()
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    std::string loadingScreenName = "LOADING DATA...";
    int fontSize = 60;
    int fontWidth = MeasureText(loadingScreenName.c_str(), fontSize);
    const float rotSpeed = 100.f;
    float rotation = GetTime() * rotSpeed;
    const float rectSizeOuter = 100.f;
    const float rectSizeInnter = 80.f;
    Rectangle rectOuter{ width / 2.f, height / 2.f - 70.f, rectSizeOuter, rectSizeOuter };
    Rectangle rectInner{ width / 2.f, height / 2.f - 70.f, rectSizeInnter, rectSizeInnter };
    Vector2 orginOuter{ rectSizeOuter / 2.f, rectSizeOuter / 2.f };
    Vector2 orginInnter{ rectSizeInnter / 2.f, rectSizeInnter / 2.f };
    BeginDrawing();
    ClearBackground(Color{ 30,30,30,255 });
    DrawRectanglePro(rectOuter, orginOuter, rotation, Color{ 230,230,230,255 });
    DrawRectanglePro(rectInner, orginInnter, rotation, Color{ 30,30,30,255 });
    DrawText(loadingScreenName.c_str(), (width - fontWidth) / 2.f, (height - fontSize) / 2.f + 70.f, fontSize, Color{230,230,230,255});
    EndDrawing();
    return true;
}

void Struktur::Core::Game()
{

    skGameData gameData;
    InitWindow(1280, 720, "Struktur Engine");
    SetTargetFPS(60);
    gameData.shouldQuit = false;

    // create task to load game
    Util::skTask<Struktur::Core::skGameData*> loadingTask(LoadData);
    loadingTask.Launch(&gameData);

    const double startTime = GetTime();
    while (!gameData.shouldQuit)
    {
        if (WindowShouldClose()) 
        {
            gameData.shouldQuit = true;
        }

        if (SplashScreen(startTime))
        {
            continue;
        }
        if (!loadingTask.complete())
        {
            // TODO some way to force a min time to display the loading screen
            LoadingScreen();
            continue;
        }

        //physics 
        //script
        //camera
        //animation
        System::Player::Update(gameData.registry);
        System::Render::Update(gameData.registry);
    }

    CloseWindow();
}