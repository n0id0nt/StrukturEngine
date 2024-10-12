#include "skRenderSystem.h"
#include "ECS/Component/skTransformComponent.h"
#include "ECS/Component/skSpriteComponent.h"
#include "ECS/Component/skTileMapComponent.h"
#include "ECS/Component/skCameraComponent.h"
#include "ECS/Component/skIdentifierComponent.h"
#include "raylib.h"
#include "Core/skResourcePool.h"
#include <cmath>

struct spriteDraw {
    Texture2D texture;
    Rectangle sourceRect;
    Rectangle destRect;
    Vector2 offset;
    float angle;
};

void Struktur::System::Render::Update(entt::registry& registry, const Core::skResourcePool& resourcePool, const Game::skCamera& camera)
{
    BeginMode2D(camera);
    std::vector<spriteDraw> lateSprites;
    {
        auto view = registry.view<Struktur::Component::skTransformComponent, Struktur::Component::skSpriteComponent, Struktur::Component::skIdentifierComponent>();
        for (auto [entity, transform, sprite, identifier] : view.each())
        {
            
            Texture2D texture = resourcePool.RetrieveTexture(sprite.imagePath);

            Vector3 spritePosition = transform.GetWorldPosition();
            float spriteRotation = transform.GetAngle();
            Vector3 spriteScale = transform.GetScale();
            Rectangle destRec{ round(spritePosition.x * 2) / 2, round(spritePosition.y * 2) / 2, sprite.size.x * spriteScale.x, sprite.size.y * spriteScale.x };
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
            Rectangle sourceRec = sprite.sourceRec;
            sourceRec.x += 0.0001f;
            sourceRec.y += 0.0001f;
            sourceRec.width -= 0.0002f;
            sourceRec.height -= 0.0002f;
            if (identifier.type == "PlayerHusk")
            {
                DrawTexturePro(texture, sourceRec, destRec, sprite.offset, spriteRotation, WHITE);
            }
            else
            {
                lateSprites.push_back(spriteDraw{ texture, sourceRec, destRec, sprite.offset, spriteRotation });
            }
        }
    }
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
                // this stops you from seeing a little bit of the neighboring sprite
                sourceRec.x += 0.0001f;
                sourceRec.y += 0.0001f;
                sourceRec.width -= 0.0002f;
                sourceRec.height -= 0.0002f;
                Rectangle DestRec{ gridTile.position.x, gridTile.position.y, tileMap.tileSize, tileMap.tileSize };
                DrawTexturePro(texture, sourceRec, DestRec, Vector2{ 0,0 }, 0, WHITE);
            }
        }
    }
    for (auto& sprite : lateSprites)
    {
        DrawTexturePro(sprite.texture, sprite.sourceRect, sprite.destRect, sprite.offset, sprite.angle, WHITE);
    }
    EndMode2D();
}
