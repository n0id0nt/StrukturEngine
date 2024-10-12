#pragma once
#include <entt/entt.hpp>
#include "skResourcePool.h"
#include "FileLoading/skLevelParser.h"
#include "Scripting/skLuaState.h"
#include "Game/skCamera.h"
#include "Physics/skPhysicsWorld.h"
#include "ECS/System/skUISystem.h"
#include "skInput.h"

namespace Struktur
{
	namespace Core
	{
		struct skGameData
		{
			bool shouldQuit;
			float pausedTime = 0.0f;
			entt::registry registry;
			skResourcePool resourcePool;
			FileLoading::LevelParser::skWorld world;
			Scripting::skLuaState luaState;
			skInput input;
			Game::skCamera camera;
			skDialogueText dialogueText;
			skGameState gameState = skGameState::MAIN_MENU;
			skGameState previousGameState = skGameState::PAUSE;
			std::unique_ptr<Physics::skPhysicsWorld> physicsWorld;
			int cutSceneIndex = 1;

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};

