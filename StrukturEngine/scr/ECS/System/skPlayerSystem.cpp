#include "skPlayerSystem.h"
#include "../Component/skTransformComponent.h"
#include "../Component/skPlayerComponent.h"

void Struktur::System::Player::Update(entt::registry& registry)
{
    auto view = registry.view<Struktur::Component::skTransformComponent, Struktur::Component::skPlayerComponent>();

    for (auto [entity, transform] : view.each())
    {
        transform.translation.x += (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
        transform.translation.y += (int)IsKeyDown(KEY_DOWN) - (int)IsKeyDown(KEY_UP);
    }
}
