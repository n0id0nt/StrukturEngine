#pragma once
#include "../../../Scripting/skLuaState.h"
#include "box2d\box2d.h"
#include "raylib.h"
#include <set>
#include <string>
#include <vector>
#include "skCollisionBodyComponent.h"
#include "../skTileMapComponent.h"
namespace Struktur
{
    namespace Component
    {
        class skTileMapCollisionBodyComponent : public skCollisionBodyComponent
        {
        public:
            skTileMapCollisionBodyComponent(Physics::skPhysicsWorld* world, const skTileMapComponent& tilemap, entt::entity entity, bool isSensor, uint16 categoryBits, uint16 maskBits);

            static void LUABind(Scripting::skLuaState& lua);

        private:

            enum class Dir {
                Right,
                Down,
                Left,
                Up,

                Count
            };

            // Custom hash function for glm::ivec2
            struct IVec2Hash
            {
                std::size_t operator()(const glm::ivec2& v) const {
                    // Combine hash values of each component
                    std::hash<unsigned int> hasher;
                    std::size_t hash = hasher(v.x);
                    hash ^= hasher(v.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
                    return hash;
                }
            };

            bool IsTileClearAtDir(glm::ivec2 tile, const skTileMapComponent& tilemap, Dir inputDir);
            Dir NextDir(Dir inputDir);
            Dir PreviousDir(Dir inputDir);
            bool IsNextDirClear(glm::ivec2 tile, const skTileMapComponent& tilemap, Dir inputDir);
            glm::ivec2 GetTileInDir(glm::ivec2 tile, Dir inputDir);
            void CreateLoop(Dir inputDir, glm::ivec2 inputTile, std::unordered_set<glm::ivec2, IVec2Hash>& checkedTiles, const skTileMapComponent& tilemap, bool isSensor, const b2Filter& filter);
            std::array<b2Vec2, 2> GetSideLine(Dir inputDir, glm::ivec2 inputTile, const skTileMapComponent& tilemap);
        };
    };
};
