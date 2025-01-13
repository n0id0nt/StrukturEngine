#pragma once
#include "Game/skLevel.h"
#include "Scripting/skLuaState.h"
#include <string>

namespace Struktur
{
	namespace Component
	{
		struct skLevelComponent
		{
			std::string levelId;

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};

