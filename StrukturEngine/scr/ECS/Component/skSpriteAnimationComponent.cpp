#include "skSpriteAnimationComponent.h"

void LUA_AddAnimation(Struktur::Component::skSpriteAnimationComponent& animationComponent, const std::string& animationName, const Struktur::Animation::skSpriteAnimation& animation)
{
	auto it = animationComponent.animations.find(animationName);
	if (it == animationComponent.animations.end())
	{
		animationComponent.animations[animationName] = animation;
	}
	else
	{
		assert(false); // animation already exists
	}
}

void LUA_PlayAnimation(Struktur::Component::skSpriteAnimationComponent& animationComponent, const std::string& animation, float startTime)
{
	animationComponent.curAnimation = animation;
	animationComponent.animationStartTime = startTime;
}

std::string LUA_GetCurrentAnimation(Struktur::Component::skSpriteAnimationComponent& animationComponent)
{
	return animationComponent.curAnimation;
}


bool LUA_IsAnimationPlaying(Struktur::Component::skSpriteAnimationComponent& animationComponent, float systemTime)
{
	Struktur::Animation::skSpriteAnimation curAnimation = animationComponent.animations[animationComponent.curAnimation];
	float animationTime = systemTime - animationComponent.animationStartTime;
	return curAnimation.loop || animationTime <= curAnimation.animationTime;
}

void Struktur::Component::skSpriteAnimationComponent::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skSpriteAnimationComponent>("spriteAnimationComponent"
		, "playAnimation", &LUA_PlayAnimation
		, "getCurAnimation", &LUA_GetCurrentAnimation
		, "isAnimationPlaying", &LUA_IsAnimationPlaying
		, "addAnimation", &LUA_AddAnimation
	);
}
