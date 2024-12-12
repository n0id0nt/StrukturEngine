#pragma once
#include <string>
#include <entt/entt.hpp>
#include "Scripting/skLuaState.h"

namespace Struktur
{
	namespace Entity
	{
		class skEntity
		{
			skEntity(const std::string& name, entt::registry* registry);

			skEntity(const skEntity&) = delete;

			entt::entity GetEntityId() const;

			std::string GetName() const;

			void SetChild(skEntity* entity);
			void SetParent(skEntity* entity);

			// schedules the deletion of the entity at the end of the current frame
			void Delete();
			bool IsMarkedForDeletion();

			void RemoveChild(skEntity* entity);
			void RemoveParent();

			void AddTag(const std::string& tag);
			void RemoveTag(const std::string& tag);
			bool HasTag(const std::string& tag);

			const std::vector<skEntity*>& GetChildren() const;
			skEntity* GetParent() const;

			bool GetIsIndependentFromLevel() const;

			template <typename ComponentType, typename... Args>
			ComponentType& CreateComponent(Args&&... args) const
			{
				return m_registry->emplace<ComponentType>(m_entity, std::forward<Args>(args) ...);
			}

			template <typename ComponentType>
			ComponentType& GetComponent() const
			{
				return m_registry->get<ComponentType>(m_entity);
			}

			template <typename ComponentType>
			bool HasComponent() const
			{
				return m_registry->try_get<ComponentType>(m_entity) != nullptr;
			}

			static void LUABind(sol::state& lua);

		private:
			entt::entity m_entity;
			entt::registry* m_registry;

			skEntity* m_parent;
			std::vector<skEntity*> m_children;
			std::set<std::string> m_tags;

			std::string m_name;
			int m_uniqueHash = 0;

			bool m_isIndependentFromLevel;
			bool m_scheduledForDeletion;
		};
	}
}

