#pragma once
#include "raylib.h"

namespace Struktur
{
	namespace Game
	{
		namespace TileMap
		{
			enum class FlipBit
			{
				NONE = 0,
				HORIZONTAL = 1,
				VERTIAL = 2,
				BOTH = 3,
				COUNT
			};

			struct skGridTile
			{
				Vector2 position;
				Vector2 sourcePosition;
				FlipBit flipBit;
			};
		};
	};
};

