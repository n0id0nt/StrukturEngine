#include "skLua.h"
#include "skGameData.h"
#include "../ECS/Component/skTransformComponent.h"

void Struktur::Core::Lua::BindToLua(Util::skLuaState& luaState)
{
	skGameData::LUABind(luaState);
	Component::skTransformComponent::LUABind(luaState);

	luaState.NewUsertype<Vector3>("vector3"
		, "x", &Vector3::x
		, "y", &Vector3::y
		, "z", &Vector3::z
	);	
	luaState.NewUsertype<entt::entity>("entity");
}

void Struktur::Core::Lua::InitualiseLuaState(Util::skLuaState& luaState, const std::string& luaMainFile)
{
	luaState.ScriptFile(luaMainFile);
}

void Struktur::Core::Lua::UpdateLuaState(Util::skLuaState& luaState, float dt)
{
	luaState.Update(dt);
}
