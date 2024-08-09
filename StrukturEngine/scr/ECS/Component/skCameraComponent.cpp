#include "skCameraComponent.h"

void LUA_AddTrauma(Struktur::Component::skCameraComponent* cameraComponent, float trauma)
{
	cameraComponent->trauma += trauma;
	if (cameraComponent->trauma > 1.f) cameraComponent->trauma = 1.f;
}

void LUA_ResetTrauma(Struktur::Component::skCameraComponent* cameraComponent, float trauma)
{
	cameraComponent->trauma = 0;
}

void Struktur::Component::skCameraComponent::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skCameraComponent>("luaComponent"
		, "cameraPriority", &skCameraComponent::cameraPriority
		, "zoom", &skCameraComponent::zoom
		, "angle", &skCameraComponent::angle
		, "offset", &skCameraComponent::offset
		, "deadZone", &skCameraComponent::deadZone
		, "damping", &skCameraComponent::damping
		, "forcePosition", &skCameraComponent::forcePosition
		, "traumaTime", &skCameraComponent::traumaTime
		, "maxOffset", &skCameraComponent::maxOffset
		, "maxAngle", &skCameraComponent::maxAngle
		, "trauma", &skCameraComponent::trauma
		, "shakeAmplitude", &skCameraComponent::shakeAmplitude
		, "addTrauma", &LUA_AddTrauma
		, "resetTrauma", &LUA_ResetTrauma
	);
}
