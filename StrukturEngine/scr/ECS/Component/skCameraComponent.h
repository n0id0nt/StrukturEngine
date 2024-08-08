#pragma once
#include "raylib.h"

namespace Struktur
{
	namespace Component
	{
		struct skCameraComponent
		{
			int cameraPriority;

			float zoom;
			float angle;

			Vector2 offset;
			Vector2 deadZone;

			Vector2 damping;

			bool forcePosition;
			float traumaTime;
			float maxOffset;
			float maxAngle;
			float trauma;
			float shakeAmplitude;
		};
	};
};
