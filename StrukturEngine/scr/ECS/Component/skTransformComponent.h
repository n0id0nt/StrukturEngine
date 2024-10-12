#pragma once
#include "raylib.h"
#include "Scripting/skLuaState.h"
#include "entt\entt.hpp"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

namespace Struktur
{
	namespace Component
	{
		class skTransformComponent
		{
		public:
			skTransformComponent* parentTransform = nullptr;
			entt::entity entity;

			skTransformComponent(entt::entity entity);
			
			void SetPosition(const Vector3& position);
			void SetPosition2(const Vector2& position);
			Vector3 GetPosition();
			Vector2 GetPosition2();

			void SetWorldPosition(const Vector3& position);
			void SetWorldPosition2(const Vector2& position);
			Vector3 GetWorldPosition();
			Vector2 GetWorldPosition2();

			void SetRotation(const Vector3& rotation);
			Vector3 GetRotation();

			void SetAngle(float angle);
			float GetAngle();

			void SetScale(const Vector3& scale);
			Vector3 GetScale();

			void SetScale2(const Vector2& scale);
			Vector2 GetScale2();

			static void LUABind(Scripting::skLuaState& lua);

		private:
			glm::mat4 GetLocalMatrix();
			glm::mat4 GetWorldMatrix();

			Vector3 m_translation;
			Vector3 m_scale;
			Quaternion m_rotation;
		};
	};
};
