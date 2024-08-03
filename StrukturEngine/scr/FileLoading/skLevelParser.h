#pragma once
#include <string>
#include <entt/entt.hpp>
#include "pugixml.hpp"
#include <unordered_map>
#include <vector>
#include "raylib.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <any>

namespace Struktur
{
	namespace Core
	{
		struct skGameData;
	}
	namespace FileLoading
	{
		namespace LevelParser
		{
			enum class FieldInstanceType
			{
				INTEGER,
				FLOAT,
				BOOLEAN,
				STRING,
				MULTILINE,
				COLOUR,
				ENUM,
				FILE_PATH,
				TILE,
				ENTITY_REF,
				POINT,

				COUNT
			};

			struct skFieldInstance
			{
				std::string identifier;
				std::any value;
				FieldInstanceType type;
			};

			struct skEntity
			{
				std::string identifier;
				std::string Iid;
				Vector2 grid;
				Vector2 pivot;
				int width;
				int height;
				Vector2 px;
				int worldX;
				int worldY;
				std::vector<skFieldInstance> fieldInstances;
			};

			enum class FlipBit
			{
				NONE = 0,
				HORIZONTAL = 1,
				VERTIAL = 2,
				BOTH = 3,

				COUNT
			};

			enum class LayerType
			{
				ENTITIES,
				INT_GRID,
				AUTO_LAYER,
				TILES,
				
				COUNT
			};

			struct skGridTile
			{
				Vector2 px;
				Vector2 src;
				Vector2 d;
				FlipBit f;
				int t;
				int a;
			};

			struct skLayer
			{
				std::string identifier;
				std::string Iid;
				LayerType type;
				int cWid;
				int cHei;
				int gridSize;
				int pxTotalOffsetX;
				int pxTotalOffsetY;
				float opacity;
				std::vector<skEntity> entityInstaces;
				std::optional<std::string> tilesetRelPath;
				std::vector<int> intGrid;
				std::vector<skGridTile> autoLayerTiles;
			};

			struct skLevel
			{
				std::string identifier;
				std::string Iid;
				std::vector<skLayer> layers;
				int worldX;
				int worldY;
				int pxWid;
				int pxHei;
				std::vector<std::string> neighbours;
			};

			struct skWorld
			{
				std::string Iid;
				std::vector<skLevel> levels;
			};

			Vector2 LoadJsonVector2(const nlohmann::json& json);

			skWorld LoadWorldMap(Core::skGameData* gameData, const std::string& fileDir, const std::string& worldFile);
			void LoadLevels(skWorld& world, const nlohmann::json& json);
			void LoadLayers(skLevel& level, const nlohmann::json& json);
			void LoadEntities(skLayer& entityLayer, const nlohmann::json& json);
			void LoadFieldInstances(skEntity& entity, const nlohmann::json& json);
			void LoadIntGrid(skLayer& gridLayer, const nlohmann::json& json);
			void LoadAutoLayerTiles(skLayer& gridLayer, const nlohmann::json& json);
			FieldInstanceType ConvertFieldTypeToEnum(const std::string& fieldInstanceType);
		}
	}
}