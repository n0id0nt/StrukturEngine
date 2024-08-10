#pragma once
#include <entt/entt.hpp>
#include "raylib.h"

namespace Struktur
{
	namespace Core
	{
		class skResourcePool;
	}
	namespace Game
	{
		struct skCamera;
	}
	namespace Component
	{
		struct skCameraComponent;
	}
	namespace System
	{
		namespace Camera
		{
			void Update(float systemTime, float dt, entt::registry& registry, Game::skCamera& out_camera);

			Vector2 CalculateSmoothedPosition(float systemTime, float dt, Component::skCameraComponent* cameraComponent, const Vector2& cameraComponentPos, Game::skCamera& camera);
			Vector2 TargetPosition(float systemTime, float dt, Component::skCameraComponent* cameraComponent, const Vector2& cameraComponentPos, Game::skCamera& camera);
			void CalculateCameraShake(float systemTime, float dt, Component::skCameraComponent* cameraComponent, Game::skCamera& camera);
		};
	};
};

