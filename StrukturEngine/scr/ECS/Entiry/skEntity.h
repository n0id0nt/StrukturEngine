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

			void SetChild(std::shared_ptr<skEntity> self, std::shared_ptr<skEntity> entity);
			void SetParent(std::shared_ptr<skEntity> self, std::shared_ptr<skEntity> entity);

			// schedules the deletion of the entity at the end of the current frame
			void Delete();
			bool IsMarkedForDeletion();

			void RemoveChild(std::shared_ptr<skEntity> self, std::shared_ptr<skEntity> entity);
			void RemoveParent();

			void AddTag(const std::string& tag);
			void RemoveTag(const std::string& tag);
			bool HasTag(const std::string& tag);

			const std::vector<std::shared_ptr<skEntity>>& GetChildren() const;
			std::shared_ptr<skEntity> GetParent() const;

			bool GetIsIndependentFromLevel() const;

			template <typename ComponentType, typename... Args>
			const ComponentType* CreateComponent(Args&&... args) const
			{
				return m_registry->emplace<ComponentType>(m_entity, std::forward<Args>(args) ...);
			}

			template <typename ComponentType>
			const ComponentType* GetComponent() const
			{
				return m_registry->GetComponent<ComponentType>(m_entity);
			}

			template <typename ComponentType>
			bool HasComponent() const
			{
				return m_registry->HasComponent<ComponentType>(m_entity);
			}

			static void LUABind(sol::state& lua);

		private:
			entt::entity m_entity;
			entt::registry* m_registry;

			std::shared_ptr<skEntity> m_parent;
			std::vector<std::shared_ptr<skEntity>> m_children;
			std::set<std::string> m_tags;

			std::string m_name;
			int m_uniqueHash = 0;

			bool m_isIndependentFromLevel;
			bool m_scheduledForDeletion;
		};
	}
}

