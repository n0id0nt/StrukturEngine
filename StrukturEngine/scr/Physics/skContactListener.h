#pragma once
#include <Box2D/Box2D.h>
#include <entt\entt.hpp>
#include <vector>
#include "glm\glm.hpp"
#include "Scripting/skLuaState.h"

namespace Struktur
{
    namespace Physics
    {
        class skContactListener : public b2ContactListener {
        public:
            struct skContact {
                skContact(b2Fixture* fixture, b2Fixture* otherFixture, entt::entity other, b2Contact* contact, Scripting::skLuaState& lua);

                b2Fixture* fixture;
                b2Fixture* otherFixture;
                entt::entity other;
                sol::table contactPoints;
                sol::table impulses;
                glm::vec2 velocity;
                glm::vec2 normal;
                bool enabled;
            };

            void BeginContact(b2Contact* contact) override;
            void EndContact(b2Contact* contact) override;

            void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

        private:
            void GetContactEntities(b2Contact* contact, entt::entity entityA, entt::entity entityB);

        };
    };
};
