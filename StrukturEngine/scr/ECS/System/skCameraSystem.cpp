#include "skCameraSystem.h"
#include "../Component/skCameraComponent.h"
#include "../Component/skTransformComponent.h"
#include "../../Game/skCamera.h"
#include "../../Util/skNoise.h"
#include <raymath.h>

void Struktur::System::Camera::Update(float systemTime, float dt, entt::registry& registry, Game::skCamera& out_camera)
{
    auto view = registry.view<Struktur::Component::skCameraComponent, Struktur::Component::skTransformComponent>();

    entt::entity focusedCameraEntity;
    Struktur::Component::skCameraComponent* focusedCameraComponent = nullptr;
    Struktur::Component::skTransformComponent* focusedTransformComponent = nullptr;
    int highestPriority = INT_MIN;
    for (auto [entity, camera, transform] : view.each())
    {
        if (camera.cameraPriority > highestPriority)
        {
            highestPriority = camera.cameraPriority;
            focusedCameraEntity = entity;
            focusedCameraComponent = &camera;
            focusedTransformComponent = &transform;
        }
    }

    if (focusedCameraComponent && focusedTransformComponent)
    {
        //out_camera.target = out_camera.previousCameraPosition;
        Vector2 position = Vector2{ focusedTransformComponent->translation.x, focusedTransformComponent->translation.y };
        Vector2 newPos = focusedCameraComponent->forcePosition ? TargetPosition(systemTime, dt, focusedCameraComponent, position, out_camera)
            : CalculateSmoothedPosition(systemTime, dt, focusedCameraComponent, position, out_camera);
        focusedCameraComponent->forcePosition = false;
        out_camera.target = newPos;
        out_camera.offset = Vector2{ GetScreenWidth()/2.f, GetScreenHeight()/2.f };
        out_camera.zoom = focusedCameraComponent->zoom;
        out_camera.rotation = focusedCameraComponent->angle;
        out_camera.previousCameraPosition = newPos;
        //out_camera.previousCameraAngle = angle;

        // exclude shake from previous position
        CalculateCameraShake(systemTime, dt, focusedCameraComponent, out_camera);
    }
}

Vector2 Struktur::System::Camera::CalculateSmoothedPosition(float systemTime, float dt, Struktur::Component::skCameraComponent* cameraComponent, const Vector2& cameraComponentPos, Game::skCamera& camera)
{
	Vector2 cameraComponentScreenPos = camera.WorldPosToScreenPos(cameraComponentPos);
    Vector2 newPos{};
	// x
	{
		if (cameraComponent->offset.x + cameraComponent->deadZone.x < cameraComponentScreenPos.x)
		{
			newPos.x = Lerp(0.f, cameraComponentScreenPos.x - cameraComponent->offset.x - cameraComponent->deadZone.x, cameraComponent->damping.x * dt);
		}
		else if (cameraComponent->offset.x - cameraComponent->deadZone.x > cameraComponentScreenPos.x)
		{
			newPos.x = Lerp(0.f, cameraComponentScreenPos.x - cameraComponent->offset.x + cameraComponent->deadZone.x, cameraComponent->damping.x * dt);
		}
	}
	// y 
	{
		if (cameraComponent->offset.y + cameraComponent->deadZone.y < cameraComponentScreenPos.y)
		{
			newPos.y = Lerp(0.f, cameraComponentScreenPos.y - cameraComponent->offset.y - cameraComponent->deadZone.y, cameraComponent->damping.y * dt);
		}
		else if (cameraComponent->offset.y - cameraComponent->deadZone.y > cameraComponentScreenPos.y)
		{
			newPos.y = Lerp(0.f, cameraComponentScreenPos.y - cameraComponent->offset.y + cameraComponent->deadZone.y, cameraComponent->damping.y * dt);
		}
	}

    return camera.ScreenPosToWorldPos(newPos);
}

Vector2 Struktur::System::Camera::TargetPosition(float systemTime, float dt, Struktur::Component::skCameraComponent* cameraComponent, const Vector2& cameraComponentPos, Game::skCamera& camera)
{
    return cameraComponentPos;
}

void Struktur::System::Camera::CalculateCameraShake(float systemTime, float dt, Struktur::Component::skCameraComponent* cameraComponent, Game::skCamera& camera)
{
    float trauma = cameraComponent->trauma;
    if (trauma > 0.f)
    {
        const int seed = 0;
        float shake = std::pow(trauma, 2.f);
        float angle = cameraComponent->maxAngle * shake * Util::Noise::PerlinNoise1(seed, systemTime / cameraComponent->shakeAmplitude);
        float xOffset = cameraComponent->maxOffset * shake * Util::Noise::PerlinNoise1(seed + 1, systemTime / cameraComponent->shakeAmplitude);
        float yOffset = cameraComponent->maxOffset * shake * Util::Noise::PerlinNoise1(seed + 2, systemTime / cameraComponent->shakeAmplitude);

        cameraComponent->trauma = trauma - dt / cameraComponent->traumaTime;
        camera.target = Vector2{ camera.target.x + xOffset, camera.target.y + yOffset };
        camera.previousCameraAngle = camera.rotation + angle;
    }
    else
    {
        cameraComponent->trauma = 0;
    }
}
