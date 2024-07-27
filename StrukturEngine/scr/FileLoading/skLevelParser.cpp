#include "skLevelParser.h"
#include <fstream>
#include "raylib.h"
#include <format>

Vector2 Struktur::FileLoading::LevelParser::LoadJsonVector2(const nlohmann::json& json)
{
	Vector2 vector{ json[0], json[1] };
	return vector;
}

Struktur::FileLoading::LevelParser::skWorld Struktur::FileLoading::LevelParser::LoadWorldMap(Core::skGameData* gameData, const std::string& fileDir, const std::string& worldFile)
{
	std::string filePath(fileDir + worldFile);
	std::ifstream file(filePath);
	assert(file);
	nlohmann::json data = nlohmann::json::parse(file);
	file.close();

	TraceLog(LOG_INFO, "Loading world");

	skWorld world;
	world.Iid = data["iid"];

	LoadLevels(world, data["levels"]);

	return world;
}

void Struktur::FileLoading::LevelParser::LoadLevels(skWorld& world, const nlohmann::json& json)
{
	for (auto& levelJson : json)
	{
		std::string levelName = levelJson["identifier"];
		TraceLog(LOG_INFO, std::format("Loading level {}", levelName).c_str());

		skLevel level;
		level.identifier = levelName;
		level.Iid = levelJson["iid"];
		level.worldX = levelJson["worldX"];
		level.worldY = levelJson["worldY"];
		level.pxWid = levelJson["pxWid"];
		level.pxHei = levelJson["pxHei"];
		LoadLayers(level, levelJson["layerInstances"]);
		world.levels.push_back(level);
	}
}

void Struktur::FileLoading::LevelParser::LoadLayers(skLevel& level, const nlohmann::json& json)
{
	for (auto& layerJson : json)
	{
		std::string layerName = layerJson["__identifier"];
		TraceLog(LOG_INFO, std::format("Loading layer {}", layerName).c_str());

		std::string layerType = layerJson["__type"];
		skLayer layer;
		if (layerType == "Entities")
		{
			layer.type = LayerType::ENTITIES;
			LoadEntities(layer, layerJson["entityInstances"]);
		}
		else if (layerType == "IntGrid" || layerType == "AutoLayer")
		{
			if (layerType == "IntGrid")
			{
				layer.type = LayerType::INT_GRID;
				LoadIntGrid(layer, layerJson["intGridCsv"]);
			}
			else if (layerType == "AutoLayer")
			{
				layer.type = LayerType::AUTO_LAYER;
			}
			layer.tilesetRelPath = layerJson["__tilesetRelPath"];
			LoadAutoLayerTiles(layer, layerJson["autoLayerTiles"]);
		}
		
		layer.identifier = layerName;
		layer.Iid = layerJson["iid"];
		layer.cWid = layerJson["__cWid"];
		layer.cHei = layerJson["__cHei"];
		layer.gridSize = layerJson["__gridSize"];
		layer.pxTotalOffsetX = layerJson["__pxTotalOffsetX"];
		layer.pxTotalOffsetY = layerJson["__pxTotalOffsetY"];
		layer.opacity = layerJson["__opacity"];

		level.layers.push_back(layer);
	}
}

void Struktur::FileLoading::LevelParser::LoadEntities(skLayer& entityLayer, const nlohmann::json& json)
{
	for (auto& entityJson : json)
	{
		std::string entityName = entityJson["__identifier"];
		TraceLog(LOG_INFO, std::format("Loading entity {}", entityName).c_str());

		skEntity entity;
		entity.identifier = entityName;
		entity.Iid = entityJson["iid"];
		entity.grid = LoadJsonVector2(entityJson["__grid"]);
		entity.pivot = LoadJsonVector2(entityJson["__pivot"]);
		entity.width = entityJson["width"];
		entity.height = entityJson["height"];
		entity.px = LoadJsonVector2(entityJson["px"]);
		LoadFieldInstances(entity, entityJson["fieldInstances"]);

		entityLayer.entityInstaces.push_back(entity);
	}
}

void Struktur::FileLoading::LevelParser::LoadFieldInstances(skEntity& entity, const nlohmann::json& json)
{
	for (auto& fieldInstanceJson : json)
	{
		std::string fieldName = fieldInstanceJson["__identifier"];
		TraceLog(LOG_INFO, std::format("Loading field instance {}", fieldName).c_str());

		skFieldInstance field;
		field.identifier = fieldName;

		entity.fieldInstances.push_back(field);
	}
}

void Struktur::FileLoading::LevelParser::LoadIntGrid(skLayer& gridLayer, const nlohmann::json& json)
{
	TraceLog(LOG_INFO, "Loading int grid");
	//gridLayer.intGrid.resize(json.size());
	for (auto& intGridJson : json)
	{
		gridLayer.intGrid.push_back(intGridJson);
	}
}

void Struktur::FileLoading::LevelParser::LoadAutoLayerTiles(skLayer& gridLayer, const nlohmann::json& json)
{
	TraceLog(LOG_INFO, "Loading int grid");
	//gridLayer.autoLayerTiles.resize(json.size());
	for (auto& autoLayerTileJson : json)
	{
		skGridTile gridTile;
		gridTile.px = LoadJsonVector2(autoLayerTileJson["px"]);
		gridTile.src = LoadJsonVector2(autoLayerTileJson["src"]);
		gridTile.d = LoadJsonVector2(autoLayerTileJson["d"]);
		gridTile.f = autoLayerTileJson["f"];
		gridTile.t = autoLayerTileJson["t"];
		gridTile.a = autoLayerTileJson["a"];
		gridLayer.autoLayerTiles.push_back(gridTile);
	}
}
