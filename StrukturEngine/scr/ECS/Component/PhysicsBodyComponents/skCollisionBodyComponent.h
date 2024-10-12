#pragma once
#include "Scripting/skLuaState.h"
#include "Physics/skPhysicsWorld.h"
#include "box2d\box2d.h"
#include "raylib.h"
#include <set>
#include <string>
#include <vector>
namespace Struktur
{
    namespace Component
    {
        class skCollisionBodyComponent
        {
        public:
            skCollisionBodyComponent(Physics::skPhysicsWorld* world);
            skCollisionBodyComponent(const skCollisionBodyComponent&) = delete;
            virtual ~skCollisionBodyComponent();

            b2Body* GetBody() const;

            void SetVelocity(Vector2 velocity);
            Vector2 GetVelocity();

            Vector2 GetPosition();
            void SetPosition(Vector2 pos);

            // only used for debugging should eventually be changed to a more generic collision shape to draw more abstract fixtures
            // could take something from the tilemap collider to help draw more generic shapes???
            Vector2 GetCollisionShape();

            bool CheckCollisionAtAngle(float angle, float groundAngleBuffer);
            bool CheckGrounded(float groundAngleBuffer);

            unsigned int GetCollisionLayersMask();
            std::set<std::string> GetCollisionLayers();

            std::vector<b2Contact*> GetContacts();

            bool GetIsSensor();
            void SetIsSensor(bool isSensor);

            sol::table LUAGetCollisionLayers();

            static void LUABind(Scripting::skLuaState& lua);
            static bool IsBodySensor(b2Body* body);

        protected:
            b2FixtureDef CopyFixture(b2Fixture* fixture);

            b2Body* m_body;
            Physics::skPhysicsWorld* m_world;
            Vector2 m_collisionShape;
        };
    };
};
