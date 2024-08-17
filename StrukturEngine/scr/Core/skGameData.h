#pragma once
#include <entt/entt.hpp>
#include "skResourcePool.h"
#include "../FileLoading/skLevelParser.h"
#include "../Scripting/skLuaState.h"
#include "../Game/skCamera.h"
#include "../Physics/skPhysicsWorld.h"
#include "skInput.h"

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
			std::unique_ptr<Physics::skPhysicsWorld> physicsWorld;

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};

