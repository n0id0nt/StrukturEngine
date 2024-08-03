#pragma once
#include "raylib.h"
#include "../../Scripting/skLuaState.h"

namespace Struktur
{
	namespace Component
	{
		struct skTransformComponent : public Transform
		{
			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};
