#include "skSpriteAnimation.h"

void Struktur::Animation::skSpriteAnimation::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skSpriteAnimation>("spriteAnimation"
		, "new", sol::constructors<skSpriteAnimation(unsigned int, unsigned int, float, bool)>()
		, "startFrame", &skSpriteAnimation::startFrame
		, "endFrame", &skSpriteAnimation::endFrame
		, "animationTime", &skSpriteAnimation::animationTime
		, "loop", &skSpriteAnimation::loop
	);
	lua["spriteAnimation"]["copy"] = sol::overload(
		[](const skSpriteAnimation& original) {
			return skSpriteAnimation(original);
		}
	);
}
