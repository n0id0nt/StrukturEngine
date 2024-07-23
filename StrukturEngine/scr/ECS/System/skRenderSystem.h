#pragma once
#include <entt/entt.hpp>

namespace Struktur
{
	namespace System
	{
		namespace Render
		{
			void Update(entt::registry& registry);
			void CreateTextures(entt::registry& registry);
		};
	};
};