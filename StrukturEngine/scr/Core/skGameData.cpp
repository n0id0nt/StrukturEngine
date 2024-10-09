#include "skGameData.h"
#include "../ECS/Component/skIdentifierComponent.h"
#include "../ECS/Component/skTransformComponent.h"
#include "../ECS/Component/skLuaComponent.h"
#include "../ECS/Component/skCameraComponent.h"
#include "../ECS/Component/skSpriteComponent.h"
#include "../ECS/Component/skSpriteAnimationComponent.h"
#include "../ECS/Component/skTileMapComponent.h"

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

void LUA_PlaySound(Struktur::Core::skGameData& gameData, const std::string& a_sound)
{
	Sound sound = gameData.resourcePool.RetrieveSound(a_sound);
	PlaySound(sound);
}

void LUA_StopSound(Struktur::Core::skGameData& gameData, const std::string& a_sound)
{
	Sound sound = gameData.resourcePool.RetrieveSound(a_sound);
	StopSound(sound);
}

bool LUA_IsSoundPlaying(Struktur::Core::skGameData& gameData, const std::string& a_sound)
{
	Sound sound = gameData.resourcePool.RetrieveSound(a_sound);
	return IsSoundPlaying(sound);
}

void Struktur::Core::skGameData::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skDialogueText>("dialogueText"
		,"name", &skDialogueText::name
		,"paragraph", &skDialogueText::paragraph
		,"startTime", &skDialogueText::startTime
		,"showAllText", &skDialogueText::showAllText
		,"dialogueVisible", &skDialogueText::dialogueVisible
	);

	lua.NewEnum("eGameState"
		, "MainMenu", skGameState::MAIN_MENU
		, "Game", skGameState::GAME
		, "Pause", skGameState::PAUSE
		, "CutScene", skGameState::CUT_SCENE
		, "Count", skGameState::COUNT
	);

	lua.NewUsertype<skGameData>("gameData"
		,"resourcePool", &skGameData::resourcePool
		,"world", &skGameData::world
		,"input", &skGameData::input
		,"dialogueText", &skGameData::dialogueText
		,"shouldQuit", &skGameData::shouldQuit
		,"gameState", &skGameData::gameState
		,"previousGameState", &skGameData::previousGameState
		,"cutSceneIndex", &skGameData::cutSceneIndex
		//,"registry", &skGameData::registry
		// Get components
		,"getEntitiesWithIdentifier", &LUA_GetEntitiesWithIdentifier
		,"getEntityWithIdentifier", &LUA_GetEntityWithIdentifier
		,"getTransformComponentsTable", &LUA_GetEntitiesAndComponentsOfType<Component::skTransformComponent>
		,"getTileMapComponentsTable", &LUA_GetEntitiesAndComponentsOfType<Component::skTileMapComponent>
		,"getTransformComponent", &LUA_GetComponentFromEntity<Component::skTransformComponent>
		,"getLuaComponent", &LUA_GetComponentFromEntity<Component::skLuaComponent>
		,"getCameraComponent", &LUA_GetComponentFromEntity<Component::skCameraComponent>
		,"getSpriteComponent", &LUA_GetComponentFromEntity<Component::skSpriteComponent>
		,"getSpriteAnimationComponent", &LUA_GetComponentFromEntity<Component::skSpriteAnimationComponent>
		// create components
		,"createCameraComponent", &LUA_CreateComponent<Component::skCameraComponent>
		,"createSpriteComponent", &LUA_CreateComponent<Component::skSpriteComponent>
		,"createSpriteAnimationComponent", &LUA_CreateComponent<Component::skSpriteAnimationComponent>
		,"playSound", &LUA_PlaySound
		,"stopSound", &LUA_StopSound
		,"isSoundPlaying", &LUA_IsSoundPlaying
	);
}
