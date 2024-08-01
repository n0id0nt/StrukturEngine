#include "skTransformComponent.h"

void Struktur::Component::skTransformComponent::LUABind(Util::skLuaState& lua)
{
	lua.NewUsertype<skTransformComponent>("transformComponent"
		, "translation", &skTransformComponent::translation
	);
}
