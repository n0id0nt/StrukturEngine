#pragma once

#include "skLuaState.h"
#include "entt\entt.hpp"

namespace Struktur
{
	namespace Scripting
	{
		class skLuaScriptTemplate
		{
		public:
			skLuaScriptTemplate();
			~skLuaScriptTemplate() {}

			static void LUABind(Scripting::skLuaState& lua);

		private:
			std::function<void(entt::entity)> m_createFunction;
			std::function<void(entt::entity, float)> m_updateFunction;
			std::function<void(entt::entity)> m_destroyFunction;
		};
	};
};