#pragma once
#include "Scripting/skLuaState.h"
#include "skGameData.h"

namespace Struktur
{
	namespace Core
	{
		namespace Lua
		{
			void BindToLua(Scripting::skLuaState& luaState);

			void CreateLuaStateScript(Scripting::skLuaState& luaState, const std::string& luaMainFile);

			void InitualiseLuaState(Scripting::skLuaState& luaState, float systemTime);

			void UpdateLuaState(Scripting::skLuaState& luaState, float dt, float systemTime);
		};
	};
};


