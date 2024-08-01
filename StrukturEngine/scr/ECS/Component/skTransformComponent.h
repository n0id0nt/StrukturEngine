#pragma once
#include "raylib.h"
#include "../../Util/skLuaState.h"

namespace Struktur
{
	namespace Component
	{
		struct skTransformComponent : public Transform
		{
			static void LUABind(Util::skLuaState& lua);
		};
	};
};
