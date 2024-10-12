#include "skAnimationSystem.h"
#include "ECS/Component/skSpriteAnimationComponent.h"
#include "ECS/Component/skSpriteComponent.h"
#include "Animation/skSpriteAnimation.h"

void Struktur::System::Animation::Update(float systemTime, float dt, entt::registry& registry)
{
	auto view = registry.view<Component::skSpriteComponent, Component::skSpriteAnimationComponent>();
	for (auto [entity, sprite, spriteAnimation] : view.each())
	{
		// get the current animation frame
		float animationTime = systemTime - spriteAnimation.animationStartTime;
		Struktur::Animation::skSpriteAnimation curAnimation = spriteAnimation.animations[spriteAnimation.curAnimation];
		if (curAnimation.loop) 
		{
			animationTime = fmod(animationTime, curAnimation.animationTime);
		}
		else if (animationTime > curAnimation.animationTime)
		{
			animationTime = curAnimation.animationTime;
		}

		int frame = curAnimation.startFrame + (int)std::floor((curAnimation.endFrame - curAnimation.startFrame) * animationTime / curAnimation.animationTime);
		sprite.SetSpriteIndex(frame);
	}

}
