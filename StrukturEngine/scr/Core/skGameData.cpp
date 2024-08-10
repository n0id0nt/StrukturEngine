#include "skGameData.h"
#include "../ECS/Component/skIdentifierComponent.h"
#include "../ECS/Component/skTransformComponent.h"
#include "../ECS/Component/skLuaComponent.h"
#include "../ECS/Component/skCameraComponent.h"
#include "../ECS/Component/skSpriteComponent.h"

entt::entity LUA_GetEntityWithIdentifier(Struktur::Core::skGameData& gameData, const std::string& identifier)
{
	auto view = gameData.registry.view<Struktur::Component::skIdentifierComponent>();
	for (auto [entity, identifierComponent] : view.each())
	{
		if (identifierComponent.type == identifier)
		{
			return entity;
		}
	}

	assert(false);
	return entt::entity();
}

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
		entitiesTable[entity] = component;
	}

	return entitiesTable;
}

template<typename Component>
Component& LUA_GetComponentFromEntity(Struktur::Core::skGameData& gameData, const entt::entity& entity)
{
	Component& component = gameData.registry.get<Component>(entity);
	return component;
}

template<typename Component, typename... Args>
Component& LUA_CreateComponent(Struktur::Core::skGameData& gameData, const entt::entity& entity, Args &&...args)
{
	Component& component = gameData.registry.emplace<Component>(entity, std::forward<Args>(args)...);
	return component;
}

void Struktur::Core::skGameData::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skGameData>("gameData"
		,"resourcePool", &skGameData::resourcePool
		,"world", &skGameData::world
		,"input", &skGameData::input
		//,"registry", &skGameData::registry
		// Get components
		,"getEntitiesWithIdentifier", &LUA_GetEntitiesWithIdentifier
		,"getEntityWithIdentifier", &LUA_GetEntityWithIdentifier
		,"getTransformComponentsTable", &LUA_GetEntitiesAndComponentsOfType<Component::skTransformComponent>
		,"getTransformComponent", &LUA_GetComponentFromEntity<Component::skTransformComponent>
		,"getLuaComponent", &LUA_GetComponentFromEntity<Component::skLuaComponent>
		,"getCameraComponent", &LUA_GetComponentFromEntity<Component::skCameraComponent>
		,"getSpriteComponent", &LUA_GetComponentFromEntity<Component::skSpriteComponent>
		// create components
		,"createCameraComponent", &LUA_CreateComponent<Component::skCameraComponent>
		,"createSpriteComponent", &LUA_CreateComponent<Component::skSpriteComponent>
	);
}
