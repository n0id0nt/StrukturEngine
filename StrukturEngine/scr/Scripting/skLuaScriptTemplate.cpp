#include "skLuaScriptTemplate.h"

Struktur::Scripting::skLuaScriptTemplate::skLuaScriptTemplate()
{
}

void Struktur::Scripting::skLuaScriptTemplate::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skLuaScriptTemplate>("scriptTemplate"
		, "new", sol::constructors<skLuaScriptTemplate()>()
		, "create", &skLuaScriptTemplate::m_createFunction
		, "update", &skLuaScriptTemplate::m_updateFunction
		, "destroy", &skLuaScriptTemplate::m_destroyFunction
	);
}
