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
		};
	};
};

