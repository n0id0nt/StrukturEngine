#pragma once
#include "../../../Scripting/skLuaState.h"
#include "box2d\box2d.h"
#include "raylib.h"
#include <set>
#include <string>
#include <vector>
#include "skCollisionBodyComponent.h"
namespace Struktur
{
    namespace Component
    {
        class skPhysicsBodyComponent : public skCollisionBodyComponent
        {
        public:
            skPhysicsBodyComponent(Physics::skPhysicsWorld* world, Vector2 collisionShape, entt::entity entity, bool isSensor, uint16 categoryBits, uint16 maskBits);
            skPhysicsBodyComponent(const skPhysicsBodyComponent&) = delete;

            static void LUABind(Scripting::skLuaState& lua);
        };
    };
};