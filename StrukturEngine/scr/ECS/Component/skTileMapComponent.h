#pragma once
#include <string>
#include <vector>
#include "Game/skTileMap.h"
#include "Scripting/skLuaState.h"

namespace Struktur
{
	namespace Component
	{
		struct skTileMapComponent
		{
			std::string imagePath;
			int width;
			int height;
			int tileSize;
			std::vector<Game::TileMap::skGridTile> gridTiles;
			std::vector<int> grid;

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};

