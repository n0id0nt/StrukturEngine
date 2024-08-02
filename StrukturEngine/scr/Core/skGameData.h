#pragma once
#include <entt/entt.hpp>
#include "skResourcePool.h"
#include "../FileLoading/skLevelParser.h"
#include "../Util/skLuaState.h"
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
			Util::skLuaState luaState;
			skInput input;

			static void LUABind(Util::skLuaState& lua);
		};
	};
};

