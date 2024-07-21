#include "skRenderSystem.h"
#include "../Component/skTransformComponent.h"
#include "raylib.h"

void Struktur::System::Render::Update(entt::registry& registry)
{
	auto view = registry.view<Struktur::Component::skTransformComponent>();
    BeginDrawing();

    ClearBackground(Color{ 255,255,255,255 });

	for (auto [entity, transform] : view.each()) 
    {
        DrawText("Entity", transform.transform.translation.x, transform.transform.translation.y, 20, Color{0,0,0,255});
	}

    EndDrawing();
}
