#include "skCamera.h"

Vector2 Struktur::Game::skCamera::WorldPosToScreenPos(Vector2 worldPos)
{
    return GetWorldToScreen2D(worldPos, *this);
}

Vector2 Struktur::Game::skCamera::ScreenPosToWorldPos(Vector2 screenPos)
{
    return GetScreenToWorld2D(screenPos, *this);
}
