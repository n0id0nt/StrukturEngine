#pragma once
#include <entt/entt.hpp>
#include "raylib.h"
#include "Scripting/skLuaState.h"
#include "Core/System/skResourcePool.h"

namespace Struktur
{
	namespace Component
	{
		struct skSpriteComponent
		{
			std::string imagePath;
			Vector2 size;
			Vector2 offset;
			Rectangle sourceRec;
			int columns, rows;
			int imageWidth, imageHeight;
			bool flipped; // TODO change this to an enum
			int index;

			void SetSpriteIndex(int index);
			void SetImage(const std::string& imagePath, int rows, int columns, int index, const Struktur::Core::skResourcePool& resourcePool);

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};

