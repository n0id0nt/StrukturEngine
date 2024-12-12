#include "skEntity.h"
#include "ECS/Component/skTransformComponent.h"
#include "ECS/Component/PhysicsBodyComponents/skPhysicsBodyComponent.h"
#include "ECS/Component/PhysicsBodyComponents/skStaticBodyComponent.h"
#include "ECS/Component/PhysicsBodyComponents/skTileMapCollisionBodyComponent.h"
#include "ECS/Component/skSpriteComponent.h"
#include <ECS/Component/skSpriteAnimationComponent.h>
#include <ECS/Component/skCameraComponent.h>
//#include <ECS/Component/skUIComponent.h>
#include <ECS/Component/skLevelComponent.h>

Struktur::Entity::skEntity::skEntity(const std::string& name, entt::registry* registry)
	: m_name(name), m_registry(registry), m_parent(nullptr), m_children(), m_tags(), m_isIndependentFromLevel(false), m_scheduledForDeletion(false)
{
	m_entity = registry->create();
}

entt::entity Struktur::Entity::skEntity::GetEntityId() const
{
	return m_entity;
}

std::string Struktur::Entity::skEntity::GetName() const
{
	return m_name;
}

void Struktur::Entity::skEntity::SetChild(skEntity* entity)
{
	if (entity->m_parent == this)
		return;

	entity->RemoveParent();

	m_children.push_back(entity);
	entity->m_parent = this;
}

void Struktur::Entity::skEntity::SetParent(skEntity* entity)
{
	if (m_parent == this)
		return;

	if (m_parent)
		m_parent->RemoveChild(this);

	m_parent = entity;
	m_parent->m_children.push_back(this);
}

void Struktur::Entity::skEntity::Delete()
{
	m_scheduledForDeletion = true;
}

bool Struktur::Entity::skEntity::IsMarkedForDeletion()
{
	return m_scheduledForDeletion;
}

void Struktur::Entity::skEntity::RemoveChild(skEntity* entity)
{
	if (entity->m_parent != this)
		return;
	entity->m_parent = nullptr;
	m_children.erase(std::remove(m_children.begin(), m_children.end(), entity), m_children.end());
}

void Struktur::Entity::skEntity::RemoveParent()
{
	if (!m_parent)
		return;
	auto& parentsChildren = m_parent->m_children;
	parentsChildren.erase(std::remove(parentsChildren.begin(), parentsChildren.end(), this), parentsChildren.end());
	m_parent = nullptr;
}

void Struktur::Entity::skEntity::AddTag(const std::string& tag)
{
	m_tags.insert(tag);
}

void Struktur::Entity::skEntity::RemoveTag(const std::string& tag)
{
	m_tags.erase(tag);
}

bool Struktur::Entity::skEntity::HasTag(const std::string& tag)
{
	return m_tags.contains(tag);
}

const std::vector<Struktur::Entity::skEntity*>& Struktur::Entity::skEntity::GetChildren() const
{
	return m_children;
}

Struktur::Entity::skEntity* Struktur::Entity::skEntity::GetParent() const
{
	return m_parent;
}

bool Struktur::Entity::skEntity::GetIsIndependentFromLevel() const
{
	return m_isIndependentFromLevel;
}

void Struktur::Entity::skEntity::LUABind(sol::state& lua)
{
	lua.new_usertype<skEntity>("GO",
		"getName", &skEntity::GetName,
		"getTransform", &skEntity::GetComponent<Struktur::Component::skTransformComponent>,
		"getSprite", &skEntity::GetComponent<Struktur::Component::skSpriteComponent>,
		"getSpriteAnimation", &skEntity::GetComponent<Struktur::Component::skSpriteAnimationComponent>,
		"getPhysicsBody", &skEntity::GetComponent<Struktur::Component::skPhysicsBodyComponent>,
		"getStaticBody", &skEntity::GetComponent<Struktur::Component::skStaticBodyComponent>,
		"getTileMapCollisionBodyComponent", &skEntity::GetComponent<Struktur::Component::skTileMapCollisionBodyComponent>,
		"getCamera", &skEntity::GetComponent<Struktur::Component::skCameraComponent>,
		"getLevel", &skEntity::GetComponent<Struktur::Component::skLevelComponent>,
		"addTag", &skEntity::AddTag,
		"removeTag", &skEntity::RemoveTag,
		"hasTag", &skEntity::HasTag
	);
}
