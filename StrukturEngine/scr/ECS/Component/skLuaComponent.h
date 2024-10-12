#pragma once
#include <sol/sol.hpp>
#include "Scripting/skLuaState.h"

namespace Struktur
{
	namespace Component
	{
		struct skLuaComponent
		{
			bool initalised;
			sol::table table;

			static void LUABind(Scripting::skLuaState& lua);
		};
	};
};
