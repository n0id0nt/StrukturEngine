#pragma once
#include <entt/entt.hpp>

namespace Struktur
{
	namespace Core
	{
		class skResourcePool;
	}
	namespace System
	{
		namespace UI
		{
			void Update(entt::registry& registry, const Core::skResourcePool& resourcePool);
		};
	};
};
