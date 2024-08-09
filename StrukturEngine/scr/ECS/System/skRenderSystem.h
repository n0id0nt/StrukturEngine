#pragma once
#include <entt/entt.hpp>
#include "../../Game/skCamera.h"

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
			void Update(entt::registry& registry, const Core::skResourcePool& resourcePool, const Game::skCamera& camera);
		};
	};
};