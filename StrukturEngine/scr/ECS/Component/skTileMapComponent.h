#pragma once
#include <string>
#include <vector>
#include "../../Game/skTileMap.h"
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
		};
	};
};

