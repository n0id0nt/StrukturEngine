#pragma once
#include <entt/entt.hpp>

namespace Struktur
{
	namespace Entity
	{
		class skRegistry
		{
		public:
			skRegistry();
            ~skRegistry();

            entt::entity CreateEntity();
            void DeleteEntity(entt::entity entityId);

            // Add a component to an entity
            template <typename ComponentType, typename... Args>
            ComponentType* AddComponent(entt::entity entityId, Args&&... args);

            // Get a component from an entity
            template <typename ComponentType>
            ComponentType* GetComponent(EntityId entityId);

            // Remove a component from an entity
            template <typename ComponentType>
            void RemoveComponent(EntityId entityId);

            // Check if an entity has a specific component
            template <typename ComponentType>
            bool HasComponent(EntityId entityId);

            // Retrieve all entities with a specific component type
            template <typename ComponentType>
            std::vector<EntityId> GetEntitiesWithComponent();

            // Retrieve all entities with multiple matching component types
            template <typename... ComponentTypes>
            std::vector<EntityId> GetEntitiesWithComponents();

            // Retrieve all components of type
            template <typename ComponentType>
            std::vector<ComponentType*> GetAllComponents()
            {
                std::vector<ComponentType*> components;
                std::type_index typeIndex(typeid(ComponentType));
                auto componentArrayIter = m_components.find(typeIndex);
                if (componentArrayIter != m_components.end())
                {
                    ComponentArray<ComponentType>* componentArray = dynamic_cast<ComponentArray<ComponentType>*>(componentArrayIter->second);
                    components.reserve(componentArray->m_components.size());
                    for (auto& pair : componentArray->m_components)
                    {
                        ComponentType* component = pair.second;
                        components.push_back(component);
                    }
                }
                return components;
            }

		private:
			entt::registry m_registy;
		};
	};
};
