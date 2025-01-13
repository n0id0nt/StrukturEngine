#pragma once
#include "FileLoading/skLevelParser.h"
#include <entt/entt.hpp>
#include "Core/System/skLua.h"

namespace Struktur
{
	namespace Game
	{
		namespace Level
		{
			void LoadLevelEntities(const Struktur::FileLoading::LevelParser::skLevel& level, entt::registry& registry, Struktur::Scripting::skLuaState& luaState);
		}
	};
};

