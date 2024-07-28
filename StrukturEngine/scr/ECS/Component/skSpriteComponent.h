#pragma once
#include <entt/entt.hpp>
#include "raylib.h"

namespace Struktur
{
	namespace Component
	{
		struct skSpriteComponent
		{
			std::string imagePath;
			Vector2 size;
			Rectangle sourceRec;
		};
	};
};

