#pragma once
#include "raylib.h"
#include "../../Scripting/skLuaState.h"

namespace Struktur
{
	namespace Component
	{
		struct skCameraComponent
		{
			int cameraPriority = 0;

			float zoom = 1.f;
			float angle = 0.f;

			Vector2 offset;
			Vector2 deadZone;

			Vector2 damping;

			bool forcePosition = false;
			float traumaTime = 1.f;
			float maxOffset = 0.6f;
			float maxAngle = 90.f;
			float trauma = 0.f;
			float shakeAmplitude = 0.1f;

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};
