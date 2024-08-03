#include "skTransformComponent.h"

void Struktur::Component::skTransformComponent::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skTransformComponent>("transformComponent"
		, "translation", &skTransformComponent::translation
	);
}
