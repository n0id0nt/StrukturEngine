#pragma once

#include "raylib.h"

namespace Struktur
{
	namespace Game
	{
		struct skCamera : public Camera2D
		{
			Vector2 previousCameraPosition;
			float previousCameraAngle;

			Vector2 WorldPosToScreenPos(Vector2 worldPos);
			Vector2 ScreenPosToWorldPos(Vector2 screenPos);
		};
	};
};

