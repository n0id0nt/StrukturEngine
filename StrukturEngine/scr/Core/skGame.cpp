#include "skGame.h"
#include "raylib.h"
#include "raymath.h"
#include "skGameData.h"
#include <string>
#include <vector>
#include "../Util/skTask.h"
#include "../ECS/Component/skTransformComponent.h"
#include "../ECS/Component/skPlayerComponent.h"
#include "../ECS/Component/skSpriteComponent.h"
#include "../ECS/Component/skTileMapComponent.h"
#include "../ECS/System/skRenderSystem.h"
#include "../ECS/System/skPlayerSystem.h"
#include <entt/entt.hpp>
#include "../FileLoading/skLevelParser.h"
#include "../Game/skTileMap.h"
#include "skLua.h"

std::array<std::string,3> s_textures = {
    "../ExampleGame/Tiles/spelunky_shop.png",
    "../ExampleGame/Tiles/cavesofgallet_tiles.png",
    "../ExampleGame/Tiles/Warrior_Sheet-Effect.png",
};

void LoadLevelEntities(Struktur::FileLoading::LevelParser::skLevel& level, entt::registry& registry) 
{
    //const auto levelEntity = registry.create();


    for (auto& layer : level.layers) {
    	const auto layerEntity = registry.create();
        switch (layer.type)
        {
        case Struktur::FileLoading::LevelParser::LayerType::AUTO_LAYER:
        case Struktur::FileLoading::LevelParser::LayerType::INT_GRID:
        {
            Transform transform{ {layer.pxTotalOffsetX, layer.pxTotalOffsetY},{0.f,0.f,0.f,0.f},{0.f,0.f,0.f} };
            registry.emplace<Struktur::Component::skTransformComponent>(layerEntity, transform);
            std::vector<Struktur::Game::TileMap::skGridTile> grid;
            grid.reserve(layer.autoLayerTiles.size());
            for (auto& gridTile : layer.autoLayerTiles)
            {
                Struktur::Game::TileMap::skGridTile newGridTile{gridTile.px, gridTile.src, (Struktur::Game::TileMap::FlipBit)gridTile.f};
                grid.push_back(newGridTile);
            }
            registry.emplace<Struktur::Component::skTileMapComponent>(layerEntity, s_textures[1], layer.cWid, layer.cHei, layer.gridSize, grid);
            break;
        }
        case Struktur::FileLoading::LevelParser::LayerType::ENTITIES:
        {
            Transform transform{ {layer.pxTotalOffsetX, layer.pxTotalOffsetY},{0.f,0.f,0.f,0.f},{0.f,0.f,0.f} };
            registry.emplace<Struktur::Component::skTransformComponent>(layerEntity, transform);
            registry.emplace<Struktur::Component::skPlayerComponent>(layerEntity);
            registry.emplace<Struktur::Component::skSpriteComponent>(layerEntity, s_textures[0], Vector2{ 32,32 }, Rectangle{0,0,32,32});
            break;
        }
        default:
            break;
        }
    }
}

void LoadData(Struktur::Core::skGameData* gameData)
{
    //set up lua state
    Struktur::Core::Lua::BindToLua(gameData->luaState);
    // set the lua values
    // now load the main lua file
    Struktur::Core::Lua::InitualiseLuaState(gameData->luaState, "../ExampleGame/Scripts/LUAMain.lua");

    //load image
    for (std::string texture : s_textures)
    {
        gameData->resourcePool.CreateTexture(texture);
    }

    // load level
    Struktur::FileLoading::LevelParser::skWorld world = Struktur::FileLoading::LevelParser::LoadWorldMap(gameData, "../ExampleGame/", "Levels/ExampleLDKTLevel.ldtk");
    gameData->world = world;
    Struktur::FileLoading::LevelParser::skLevel& firstLevel = world.levels[0]; // should probably actually store the first level somewhere
    LoadLevelEntities(firstLevel, gameData->registry);

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(2s);
}

void MoveResourcesToVRAM(Struktur::Core::skResourcePool& resourcePool)
{
    for (std::string texture : s_textures)
    {
        if (!resourcePool.IsTextureLoadedInGPU(texture))
        {
            resourcePool.LoadTextureInGPU(texture);
        }
    }
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
    // Fade out
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
    //DrawTexture(texture2d, 0, 0, WHITE);
    DrawText(loadingScreenName.c_str(), (width - fontWidth) / 2.f, (height - fontSize) / 2.f + 70.f, fontSize, Color{230,230,230,255});
    EndDrawing();
    return true;
}

void Struktur::Core::Game()
{
    skGameData gameData;
    InitWindow(1280, 720, "Struktur Engine");
    gameData.shouldQuit = false;

    SetTargetFPS(60);
    // load in game data from memory
    {
        // create task to load game
        Util::skTask<Struktur::Core::skGameData*> loadingTask(LoadData);
        loadingTask.Launch(&gameData);

        const double startTime = GetTime();
        bool splashScreen = true;
        while (splashScreen)
        {
            splashScreen = SplashScreen(startTime);
        }
        while (!loadingTask.complete())
        {
            // TODO some way to force a min time to display the loading screen
            LoadingScreen();
        }
        loadingTask.Join();
        // Move the images to vram
        MoveResourcesToVRAM(gameData.resourcePool);
    }

    while (!gameData.shouldQuit)
    {
        if (WindowShouldClose()) 
        {
            gameData.shouldQuit = true;
        }

        float dt = 0;

        //physics 
        //script
        Lua::UpdateLuaState(gameData.luaState, dt);
        //camera
        //animation
        System::Player::Update(gameData.registry);

        BeginDrawing();
        ClearBackground(BLACK);
        System::Render::Update(gameData.registry, gameData.resourcePool);
        EndDrawing();

    }

    CloseWindow();
}