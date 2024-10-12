#pragma once
#include <unordered_map>
#include <string>
#include "Animation/skSpriteAnimation.h"
#include "Scripting/skLuaState.h"

namespace Struktur
{
	namespace Component
	{
		struct skSpriteAnimationComponent
		{
			std::unordered_map<std::string, Animation::skSpriteAnimation> animations;

			std::string curAnimation;
			float animationStartTime;

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};
