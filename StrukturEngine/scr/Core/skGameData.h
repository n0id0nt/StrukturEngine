#pragma once
#include <entt/entt.hpp>
#include "skResourcePool.h"
#include "../FileLoading/skLevelParser.h"
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
		};
	};
};

