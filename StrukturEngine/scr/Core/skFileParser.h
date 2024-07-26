#pragma once
#include <string>
#include <entt/entt.hpp>
#include "pugixml.hpp"

namespace Struktur
{
	namespace Core
	{
		struct skGameData;
		class skTileSheet;
		namespace FileParser
		{
			void LoadWorld(Struktur::Core::skGameData& gameData, const std::string& fileDir, const std::string& worldFile);
			void LoadLevel(Struktur::Core::skGameData& gameData, const entt::entity& levelEntity);

			entt::entity& LoadTemplate(Struktur::Core::skGameData& gameData, const std::string& fileDir, const std::string& levelFile, bool unique);
			entt::entity& CreateObject(Struktur::Core::skGameData& gameData, const pugi::xml_node& object, const std::string& fileDir, const skTileSheet& tileSheet, bool unique);
			entt::entity& CreateTemplatedObject(Struktur::Core::skGameData& gameData, const std::string& levelFile);

			//Entity* LoadUILayout(Struktur::Core::skGameData& gameData, const std::string& fileDir, const std::string& levelFile);
			//std::unique_ptr<UIArea> CreateUIElement(Struktur::Core::skGameData& gameData, const pugi::xml_node& object, const std::string& fileDir);
		}
	}
}