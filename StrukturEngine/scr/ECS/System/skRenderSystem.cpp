#include "skRenderSystem.h"
#include "../Component/skTransformComponent.h"
#include "../Component/skSpriteComponent.h"
#include "raylib.h"
#include "../../Core/skResourcePool.h"

void Struktur::System::Render::Update(entt::registry& registry, const Core::skResourcePool& resourcePool)
{
	auto view = registry.view<Struktur::Component::skTransformComponent, Struktur::Component::skSpriteComponent>();
    BeginDrawing();

    ClearBackground(DARKGREEN);

	for (auto [entity, transform, sprite] : view.each()) 
    {
        Texture2D texture = resourcePool.RetrieveTexture(sprite.imagePath);
        DrawTexture(texture, transform.transform.translation.x, transform.transform.translation.y, WHITE);
        DrawText("Entity", transform.transform.translation.x, transform.transform.translation.y, 20, Color{0,0,0,255});
    }
    EndDrawing();
}
