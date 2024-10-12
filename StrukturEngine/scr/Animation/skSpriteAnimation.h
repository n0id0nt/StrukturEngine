#pragma once
#include "Scripting/skLuaState.h"

namespace Struktur
{
	namespace Animation
	{
		struct skSpriteAnimation
		{
			unsigned int startFrame;
			unsigned int endFrame;
			float animationTime;
			bool loop;

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};

