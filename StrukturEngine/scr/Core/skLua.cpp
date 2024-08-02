#include "skLua.h"
#include "skGameData.h"
#include "skInput.h"
#include "../ECS/Component/skTransformComponent.h"

void Struktur::Core::Lua::BindToLua(Util::skLuaState& luaState)
{
	skGameData::LUABind(luaState);
	Component::skTransformComponent::LUABind(luaState);
	skInput::LUABind(luaState);

	// these are values from libraries that need to be bound - Might be a good idea to move this to a separate function 
	luaState.NewUsertype<Vector3>("vec3"
		, "new", sol::constructors<Vector3(float, float, float)>()
		, "x", &Vector3::x
		, "y", &Vector3::y
		, "z", &Vector3::z
	);	
	luaState["vec3"]["copy"] = sol::overload(
		[](const Vector3& original) {
		return Vector3(original);
	}
	);
	luaState.NewUsertype<Vector2>("vec2"
		, "new", sol::constructors<Vector2(float, float)>()
		, "x", &Vector2::x
		, "y", &Vector2::y
	);	
	luaState["vec2"]["copy"] = sol::overload(
		[](const Vector2& original) {
		return Vector2(original);
	}
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
