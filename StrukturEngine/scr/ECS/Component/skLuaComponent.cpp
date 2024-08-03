#include "skLuaComponent.h"

void Struktur::Component::skLuaComponent::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skLuaComponent>("luaComponent"
		, "initalised", &skLuaComponent::initalised
		, "table", &skLuaComponent::table
	);
}
