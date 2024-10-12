#pragma once
#include <entt/entt.hpp>
#include "Physics/skPhysicsWorld.h"

namespace Struktur
{
	namespace Core
	{
		class skResourcePool;
	}
	namespace System
	{
		namespace Phsysics
		{
			void Update(entt::registry& registry, Physics::skPhysicsWorld* world);
		};
	};
};

