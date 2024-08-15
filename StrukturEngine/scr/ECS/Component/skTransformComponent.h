#pragma once
#include "raylib.h"
#include "../../Scripting/skLuaState.h"
#include "entt\entt.hpp"

namespace Struktur
{
	namespace Component
	{
		struct skTransformComponent : public Transform
		{
			skTransformComponent* parentTransform;
			entt::entity entity;
			
			static void LUABind(Scripting::skLuaState& lua);

		private:
			Matrix ToMatrix(const Transform& transform);
		};
	};
};
