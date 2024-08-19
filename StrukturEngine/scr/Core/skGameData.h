#pragma once
#include <entt/entt.hpp>
#include "skResourcePool.h"
#include "../FileLoading/skLevelParser.h"
#include "../Scripting/skLuaState.h"
#include "../Game/skCamera.h"
#include "../Physics/skPhysicsWorld.h"
#include "../ECS/System/skUISystem.h"
#include "skInput.h"

enum class skGameState
{
	MAIN_MENU,
	GAME,
	CUT_SCENE,
	PAUSE,

	COUNT

};


namespace Struktur
{
	namespace Core
	{
		struct skGameData
		{
			bool shouldQuit;
			entt::registry registry;
			skResourcePool resourcePool;
			FileLoading::LevelParser::skWorld world;
			Scripting::skLuaState luaState;
			skInput input;
			Game::skCamera camera;
			skDialogueText dialogueText;
			skGameState gameState;
			std::unique_ptr<Physics::skPhysicsWorld> physicsWorld;

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};

