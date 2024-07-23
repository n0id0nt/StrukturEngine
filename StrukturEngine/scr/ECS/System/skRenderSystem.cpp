#include "skRenderSystem.h"
#include "../Component/skTransformComponent.h"
#include "../Component/skSpriteComponent.h"
#include "raylib.h"

void Struktur::System::Render::Update(entt::registry& registry)
{
	auto view = registry.view<Struktur::Component::skTransformComponent, Struktur::Component::skSpriteComponent>();
    BeginDrawing();

    ClearBackground(Color{ 255,255,255,255 });

	for (auto [entity, transform, sprite] : view.each()) 
    {
        DrawTexture(sprite.texture, transform.transform.translation.x, transform.transform.translation.y, WHITE);
        DrawText("Entity", transform.transform.translation.x, transform.transform.translation.y, 20, Color{0,0,0,255});
	}

    EndDrawing();
}
