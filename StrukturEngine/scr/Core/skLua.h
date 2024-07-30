#pragma once
#include "../Util/skLuaState.h"
#include "skGameData.h"

namespace Struktur
{
	namespace Core
	{
		namespace Lua
		{
			void BindToLua(Util::skLuaState& luaState);

			void InitualiseLuaState(Util::skLuaState& luaState, const std::string& luaMainFile);

			void UpdateLuaState(Util::skLuaState& luaState, float dt);
		};
	};
};


