#include "skRenderSystem.h"
#include "../Component/skTransformComponent.h"
#include "../Component/skSpriteComponent.h"
#include "../Component/skTileMapComponent.h"
#include "raylib.h"
#include "../../Core/skResourcePool.h"

void Struktur::System::Render::Update(entt::registry& registry, const Core::skResourcePool& resourcePool)
{
    {
        auto view = registry.view<Struktur::Component::skTransformComponent, Struktur::Component::skTileMapComponent>();

        for (auto [entity, transform, tileMap] : view.each())
        {
            Texture2D texture = resourcePool.RetrieveTexture(tileMap.imagePath);

            for (auto& gridTile : tileMap.gridTiles)
            {
                Rectangle sourceRec{ gridTile.sourcePosition.x, gridTile.sourcePosition.y, tileMap.tileSize, tileMap.tileSize };
                switch (gridTile.flipBit)
                {
                case Game::TileMap::FlipBit::BOTH:
                    sourceRec.width *= -1;
                    sourceRec.height *= -1;
                    break;
                case Game::TileMap::FlipBit::HORIZONTAL:
                    sourceRec.width *= -1;
                    break;
                case Game::TileMap::FlipBit::VERTIAL:
                    sourceRec.height *= -1;
                    break;
                }
                Rectangle DestRec{ gridTile.position.x, gridTile.position.y, tileMap.tileSize, tileMap.tileSize };
                DrawTexturePro(texture, sourceRec, DestRec, Vector2{ 0,0 }, 0, WHITE);
            }
        }
    }
    {
        auto view = registry.view<Struktur::Component::skTransformComponent, Struktur::Component::skSpriteComponent>();
        for (auto [entity, transform, sprite] : view.each())
        {
            Texture2D texture = resourcePool.RetrieveTexture(sprite.imagePath);

            Rectangle destRec{ transform.transform.translation.x, transform.transform.translation.y, sprite.size.x, sprite.size.y };
            //switch (gridTile.flipBit)
            //{
            //case Game::TileMap::FlipBit::BOTH:
            //    sourceRec.width *= -1;
            //    sourceRec.height *= -1;
            //    break;
            //case Game::TileMap::FlipBit::HORIZONTAL:
            //    sourceRec.width *= -1;
            //    break;
            //case Game::TileMap::FlipBit::VERTIAL:
            //    sourceRec.height *= -1;
            //    break;
            //}
            DrawTexturePro(texture, sprite.sourceRec, destRec, Vector2{ 0,0 }, 0, WHITE);
        }
    }
}
