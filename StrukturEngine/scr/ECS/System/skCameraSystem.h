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
	namespace System
	{
		namespace Camera
		{
			void Update(entt::registry& registry, skCamera& out_camera);

			Vector2 CalculateSmoothedPosition(skCameraComponent& cameraComponent, const Vector2& cameraComponentPos, skCamera& camera);
			Vector2 TargetPosition(skCameraComponent& cameraComponent, const Vector2& cameraComponentPos, skCamera& camera);
			void CalculateCameraShake(skCameraComponent& cameraComponent, skCamera& camera);

			static Vector3 m_previousCameraPosition;
			static float m_previousCameraAngle;
		};
	};
};

