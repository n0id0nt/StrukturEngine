#include "skGameData.h"
#include "../ECS/Component/skIdentifierComponent.h"
#include "../ECS/Component/skTransformComponent.h"

sol::table LUA_GetEntitiesWithIdentifier(Struktur::Core::skGameData& gameData, const std::string& identifier)
{
	sol::table entitiesTable = gameData.luaState.CreateTable();

	auto view = gameData.registry.view<Struktur::Component::skIdentifierComponent>();
	for (auto [entity, identifierComponent] : view.each())
	{
		if (identifierComponent.type == identifier)
		{
			entitiesTable.add(entity);
		}
	}

	return entitiesTable;
}

template<typename Component>
sol::table LUA_GetEntitiesAndComponentsOfType(Struktur::Core::skGameData& gameData)
{
	sol::table entitiesTable = gameData.luaState.CreateTable();

	auto view = gameData.registry.view<Component>();
	for (auto [entity, component] : view.each())
	{
		entitiesTable.add(entity, component);
	}

	return entitiesTable;
}

template<typename Component>
Component& LUA_GetComponentFromEntity(Struktur::Core::skGameData& gameData, const entt::entity& entity)
{
	Component& component = gameData.registry.get<Component>(entity);
	return component;
}

void Struktur::Core::skGameData::LUABind(Util::skLuaState& lua)
{
	lua.NewUsertype<skGameData>("gameData"
		,"resourcePool", &skGameData::resourcePool
		,"world", &skGameData::world
		//,"registry", &skGameData::registry
		,"getEntitiesWithIdentifier", &LUA_GetEntitiesWithIdentifier
		,"getTransformComponentsTable", &LUA_GetEntitiesAndComponentsOfType<Component::skTransformComponent>
		,"getTransformComponent", &LUA_GetComponentFromEntity<Component::skTransformComponent>
	);
}
