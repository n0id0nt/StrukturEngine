#include "skLevelComponent.h"

void Struktur::Component::skLevelComponent::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skLevelComponent>("levelComponent"
		, "levelId", &skLevelComponent::levelId
	);
}
