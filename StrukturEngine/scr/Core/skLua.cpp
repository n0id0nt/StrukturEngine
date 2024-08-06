#include "skLua.h"
#include "skGameData.h"
#include "skInput.h"
#include "../ECS/Component/skTransformComponent.h"
#include "../ECS/Component/skLuaComponent.h"
#include "../Scripting/skLuaScriptTemplate.h"

void Struktur::Core::Lua::BindToLua(Scripting::skLuaState& luaState)
{
	skGameData::LUABind(luaState);
	skInput::LUABind(luaState);

	Component::skTransformComponent::LUABind(luaState);
	Component::skLuaComponent::LUABind(luaState);

	Scripting::skLuaScriptTemplate::LUABind(luaState);

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
	luaState.NewUsertype<Rectangle>("rectangle"
		, "new", sol::constructors<Rectangle(float, float, float, float)>()
		, "x", &Rectangle::x
		, "y", &Rectangle::y
		, "width", &Rectangle::width
		, "height", &Rectangle::height
	);	
	luaState["rectangle"]["copy"] = sol::overload(
		[](const Rectangle& original) {
		return Rectangle(original);
	}
	);

	luaState.NewUsertype<entt::entity>("entity");
}

void Struktur::Core::Lua::CreateLuaStateScript(Scripting::skLuaState& luaState, const std::string& luaMainFile)
{
	luaState.ScriptFile(luaMainFile);
}

void Struktur::Core::Lua::InitualiseLuaState(Scripting::skLuaState& luaState)
{
	luaState.Initialise();
}

void Struktur::Core::Lua::UpdateLuaState(Scripting::skLuaState& luaState, float dt)
{
	luaState.Update(dt);
}
