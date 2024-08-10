#pragma once
#include <entt/entt.hpp>
#include "raylib.h"
#include "../../Scripting/skLuaState.h"

namespace Struktur
{
	namespace Component
	{
		struct skSpriteComponent
		{
			std::string imagePath;
			Vector2 size;
			Rectangle sourceRec;

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};

