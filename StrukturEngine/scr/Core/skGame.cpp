#include "skGame.h"
#include "raylib.h"
#include "raymath.h"
#include "skGameData.h"
#include <string>
#include <vector>
#include <entt/entt.hpp>
#include "Util/skTask.h"
#include "ECS/Component/skTransformComponent.h"
#include "ECS/Component/skSpriteComponent.h"
#include "ECS/Component/skTileMapComponent.h"
#include "ECS/Component/skIdentifierComponent.h"
#include "ECS/Component/skLuaComponent.h"
#include "ECS/System/skRenderSystem.h"
#include "ECS/System/skCameraSystem.h"
#include "ECS/System/skAnimationSystem.h"
#include "ECS/System/skUISystem.h"
#include "FileLoading/skLevelParser.h"
#include "Game/skTileMap.h"
#include "Core/System/skLua.h"

std::array<std::string,2> s_textures = {
    "../ExampleGame/Tiles/cavesofgallet_tiles.png",
    "../ExampleGame/Tiles/PlayerGrowthSprites.png",
};

std::array<std::string,8> s_sounds = {
    "../ExampleGame/Sounds/jumpBig.wav",
    "../ExampleGame/Sounds/jumpMedium.wav",
    "../ExampleGame/Sounds/jumpSmall.wav",
    "../ExampleGame/Sounds/scroll.wav",
    "../ExampleGame/Sounds/transform.wav",
    "../ExampleGame/Sounds/menuMusic.wav",
    "../ExampleGame/Sounds/gameMusic.wav",
    "../ExampleGame/Sounds/grow.wav",
};

// TODO might want to load this from a file
constexpr static const unsigned int FPS = 60;
constexpr static const float TIME_STEP = 1.0f / FPS;
constexpr static const int VELOCITY_ITERATIONS = 6;
constexpr static const int POSITION_ITERATIONS = 4;

void LoadLevelEntities(Struktur::FileLoading::LevelParser::skLevel& level, entt::registry& registry, Struktur::Scripting::skLuaState& luaState)
{
    //const auto levelEntity = registry.create();


    for (auto& layer : level.layers) {
        switch (layer.type)
        {
        case Struktur::FileLoading::LevelParser::LayerType::INT_GRID:
        case Struktur::FileLoading::LevelParser::LayerType::AUTO_LAYER:
        {
    	    const auto layerEntity = registry.create();
            auto& transform = registry.emplace<Struktur::Component::skTransformComponent>(layerEntity, layerEntity);
            transform.SetPosition2(Vector2(layer.pxTotalOffsetX, layer.pxTotalOffsetY));
            std::vector<Struktur::Game::TileMap::skGridTile> grid;
            grid.reserve(layer.autoLayerTiles.size());
            for (auto& gridTile : layer.autoLayerTiles)
            {
                Struktur::Game::TileMap::skGridTile newGridTile{gridTile.px, gridTile.src, (Struktur::Game::TileMap::FlipBit)gridTile.f};
                grid.push_back(newGridTile);
            }
            registry.emplace<Struktur::Component::skTileMapComponent>(layerEntity, s_textures[0], layer.cWid, layer.cHei, layer.gridSize, grid, layer.intGrid);
            break;
        }
        case Struktur::FileLoading::LevelParser::LayerType::ENTITIES:
        {
            for (auto& entityInstance : layer.entityInstaces)
            {
                const auto layerEntity = registry.create();
                Vector2 position = entityInstance.px;
                auto& transform = registry.emplace<Struktur::Component::skTransformComponent>(layerEntity, layerEntity);
                transform.SetPosition2(Vector2(position.x, position.y));
                registry.emplace<Struktur::Component::skIdentifierComponent>(layerEntity, entityInstance.identifier);
                auto& luaComponent = registry.emplace<Struktur::Component::skLuaComponent>(layerEntity, false, luaState.CreateTable());
                for (auto fieldInstance : entityInstance.fieldInstances)
                {
                    switch (fieldInstance.type)
                    {
                    case Struktur::FileLoading::LevelParser::FieldInstanceType::FLOAT:
                    {
                        float value = std::any_cast<float>(fieldInstance.value);
                        luaComponent.table[fieldInstance.identifier] = value;
                        break;
                    }
                    case Struktur::FileLoading::LevelParser::FieldInstanceType::INTEGER:
                    {
                        int value = std::any_cast<int>(fieldInstance.value);
                        luaComponent.table[fieldInstance.identifier] = value;
                        break;
                    }
                    default:
                        assert(false);
                        break;
                    }
                }
            }
            break;
        }
        default:
            break;
        }
    }
}

void LoadData(Struktur::Core::skGameData* gameData)
{
    //load input
    gameData->input = Struktur::Core::skInput(0);
    gameData->input.LoadInputBindings("../ExampleGame/", "Settings/InputBindings/InputBindings.xml");

    gameData->physicsWorld = std::make_unique<Struktur::Physics::skPhysicsWorld>(Vector2{ 0.f, 0.f }, TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS, 1.0f);

    //set up lua state
    gameData->luaState.CreateLuaState("../ExampleGame/");
    Struktur::Core::Lua::BindToLua(gameData->luaState);
    // set the lua values
    gameData->luaState.Set("GameData", gameData);
    // now load the main lua file
    Struktur::Core::Lua::CreateLuaStateScript(gameData->luaState, "../ExampleGame/Scripts/LUAMain.lua");

    //load image
    for (std::string texture : s_textures)
    {
        gameData->resourcePool.CreateTexture(texture);
    }

    //load sounds
    InitAudioDevice();
    for (std::string sound : s_sounds)
    {
        gameData->resourcePool.CreateSound(sound);
    }

    // load level
    Struktur::FileLoading::LevelParser::skWorld world = Struktur::FileLoading::LevelParser::LoadWorldMap(gameData, "../ExampleGame/", "Levels/ExampleLDKTLevel.ldtk");
    gameData->world = world;
    Struktur::FileLoading::LevelParser::skLevel& firstLevel = world.levels[0]; // should probably actually store the first level somewhere
    LoadLevelEntities(firstLevel, gameData->registry, gameData->luaState);

    // Call initialize function now that all the entities are created
    Struktur::Core::Lua::InitualiseLuaState(gameData->luaState, GetTime());

	//using namespace std::chrono_literals;
	//std::this_thread::sleep_for(5s);
}

// This needs to be called on the main thread because this talks to the gpu
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

    std::string splashScreenName = "Struktur";
    int fontSize = 60;
    int fontWidth = MeasureText(splashScreenName.c_str(), fontSize);
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    BeginDrawing();
    ClearBackground(Color{ 0,0,0,255 });
    DrawText(splashScreenName.c_str(), (width - fontWidth) / 2.f, (height - fontSize) / 2.f, fontSize, Color{ 255,255,255,(unsigned char)textAlpha });
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
    const float rectSizeInner = 80.f;
    Rectangle rectOuter{ width / 2.f, height / 2.f - 70.f, rectSizeOuter, rectSizeOuter };
    Rectangle rectInner{ width / 2.f, height / 2.f - 70.f, rectSizeInner, rectSizeInner };
    Vector2 originOuter{ rectSizeOuter / 2.f, rectSizeOuter / 2.f };
    Vector2 originInner{ rectSizeInner / 2.f, rectSizeInner / 2.f };
    BeginDrawing();
    ClearBackground(Color{ 30,30,30,255 });
    DrawRectanglePro(rectOuter, originOuter, rotation, Color{ 230,230,230,255 });
    DrawRectanglePro(rectInner, originInner, rotation, Color{ 30,30,30,255 });
    //DrawTexture(texture2d, 0, 0, WHITE);
    DrawText(loadingScreenName.c_str(), (width - fontWidth) / 2.f, (height - fontSize) / 2.f + 70.f, fontSize, Color{230,230,230,255});
    EndDrawing();
    return true;
}

void Struktur::Core::Game()
{
    skGameData gameData;
    InitWindow(1280, 720, "Struktur");
    SetExitKey(KEY_NULL);
    gameData.shouldQuit = false;

    SetTargetFPS(FPS);
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

        float dt = GetFrameTime();

        if (gameData.gameState == skGameState::PAUSE)
        {
            gameData.pausedTime += dt;
        }
        float systemTime = GetTime() - gameData.pausedTime;

        //physics 
        Lua::UpdateLuaState(gameData.luaState, dt, systemTime);
        if (gameData.gameState != skGameState::PAUSE)
        {
            System::Animation::Update(systemTime, dt, gameData.registry);
            System::Camera::Update(systemTime, dt, gameData.registry, gameData.camera);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        System::Render::Update(gameData.registry, gameData.resourcePool, gameData.camera);
        System::UI::Update(gameData.registry, gameData.resourcePool, gameData.dialogueText, systemTime, gameData.gameState, gameData.previousGameState, gameData.shouldQuit);
        //debug render(lines and stuff)
        //render UI
        //render debug UI
        //Render IMGUI (When i actually add this)
        EndDrawing();
    }

    // destroy all entities
    gameData.registry.clear();

    // unload all the resources
    gameData.resourcePool.Clear();

    CloseWindow();
}