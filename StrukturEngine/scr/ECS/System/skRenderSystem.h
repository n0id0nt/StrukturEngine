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
		namespace Render
		{
			void Update(entt::registry& registry, const Core::skResourcePool& resourcePool);
		};
	};
};