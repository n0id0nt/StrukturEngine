#include "skTileMapComponent.h"

int LUA_GetTileAtPosition(Struktur::Component::skTileMapComponent& tileMap, int x, int y)
{
	int index = x + tileMap.width * y;
	if (index < 0 || index >= tileMap.grid.size()) 
		return 0;
	return tileMap.grid[index];
}

bool LUA_IsPositionOnTile(Struktur::Component::skTileMapComponent& tileMap, const Vector2& position)
{
	int x = std::floor(position.x / tileMap.tileSize);
	int y = std::floor(position.y / tileMap.tileSize);
	return LUA_GetTileAtPosition(tileMap, x, y) != 0;
}

void Struktur::Component::skTileMapComponent::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skTileMapComponent>("tileMapComponent"
		, "width", &skTileMapComponent::width
		, "height", &skTileMapComponent::height
		, "tileSize", &skTileMapComponent::tileSize
		, "getTileAtPosition", &LUA_GetTileAtPosition
		, "isPositionOnTile", &LUA_IsPositionOnTile
	);
}
