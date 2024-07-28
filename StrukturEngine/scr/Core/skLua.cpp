#include "skLua.h"

void Struktur::Core::Lua::InitualiseLuaState(Util::skLuaState& luaState, const std::string& luaMainFile)
{
	luaState.ScriptFile(luaMainFile);
}

void Struktur::Core::Lua::UpdateLuaState(Util::skLuaState& luaState, float dt)
{
	luaState.Update(dt);
}
