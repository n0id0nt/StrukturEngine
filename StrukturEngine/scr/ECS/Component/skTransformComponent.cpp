#include "skTransformComponent.h"
#include "glm/gtx/matrix_decompose.hpp"

Struktur::Component::skTransformComponent::skTransformComponent(entt::entity entityid) : m_translation(Vector3(0.0f, 0.0f, 0.0f)), m_scale(Vector3(1.0f,1.0f,1.0f)), m_rotation(Quaternion(0.0f, 0.0f, 0.0f, 0.0f)), entity(entityid)
{

}

glm::mat4 Struktur::Component::skTransformComponent::GetLocalMatrix()
{
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale.x, m_scale.y, m_scale.z));

	glm::vec3 euler = glm::eulerAngles(glm::quat(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.x));
	glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(euler.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMat = glm::rotate(rotationMat, glm::radians(euler.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMat = glm::rotate(rotationMat, glm::radians(euler.z), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), glm::vec3(m_translation.x, m_translation.y, m_translation.z));

	glm::mat4 modelMatrix = translationMat * rotationMat * scaleMat;

	return modelMatrix;
}

glm::mat4 Struktur::Component::skTransformComponent::GetWorldMatrix()
{
	glm::mat4 local = GetLocalMatrix();
	if (parentTransform)
	{
		return parentTransform->GetWorldMatrix() * local;
	}
	return local;
}


void Struktur::Component::skTransformComponent::SetPosition(const Vector3& position)
{
	m_translation = position;
}

void Struktur::Component::skTransformComponent::SetPosition2(const Vector2& position)
{
	m_translation = Vector3(position.x, position.y, 0.0f);
}

Vector3 Struktur::Component::skTransformComponent::GetPosition()
{
	return m_translation;
}

Vector2 Struktur::Component::skTransformComponent::GetPosition2()
{
	return Vector2(m_translation.x, m_translation.y);
}

void Struktur::Component::skTransformComponent::SetWorldPosition(const Vector3& position)
{
	m_translation = position;
	if (parentTransform)
	{
		Vector3 parentTranslation = parentTransform->GetWorldPosition();
		m_translation = Vector3{ m_translation.x - parentTranslation.x, m_translation.y - parentTranslation.y, m_translation.y - parentTranslation.y };
	}
}

void Struktur::Component::skTransformComponent::SetWorldPosition2(const Vector2& position)
{
	m_translation = Vector3{ position.x, position.y, 0.f };
	if (parentTransform)
	{
		Vector3 parentTranslation = parentTransform->GetWorldPosition();
		m_translation = Vector3{ m_translation.x - parentTranslation.x, m_translation.y - parentTranslation.y, m_translation.y - parentTranslation.y };
	}
}

Vector3 Struktur::Component::skTransformComponent::GetWorldPosition()
{
	glm::vec3 scaleVec;
	glm::quat rotationQuat{};
	glm::vec3 translationVec;
	glm::vec3 skewVec;
	glm::vec4 perspectiveVec;
	glm::decompose(GetWorldMatrix(), scaleVec, rotationQuat, translationVec, skewVec, perspectiveVec);
	return Vector3(translationVec.x, translationVec.y, translationVec.z);
}

Vector2 Struktur::Component::skTransformComponent::GetWorldPosition2()
{
	Vector3 pos = GetWorldPosition();
	return Vector2(pos.x, pos.y);
}

void Struktur::Component::skTransformComponent::SetRotation(const Vector3& rotationVec)
{
	glm::quat quaternion = glm::quat(glm::vec3(m_rotation.x, m_rotation.y, m_rotation.z));
	m_rotation = Quaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.x);
}

Vector3 Struktur::Component::skTransformComponent::GetRotation()
{
	glm::vec3 euler = glm::eulerAngles(glm::quat(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.x));
	return Vector3(euler.x, euler.y, euler.z);
}

void Struktur::Component::skTransformComponent::SetAngle(float angle)
{
	glm::quat quaternion = glm::quat(glm::vec3(0.0f, 0.0f, angle));
	m_rotation = Quaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.x);
}

float Struktur::Component::skTransformComponent::GetAngle()
{
	glm::vec3 euler = glm::eulerAngles(glm::quat(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.x));
	return euler.z;
}

void Struktur::Component::skTransformComponent::SetScale(const Vector3& scaleVec)
{
	m_scale = scaleVec;
}

Vector3 Struktur::Component::skTransformComponent::GetScale()
{
	return m_scale;
}

void Struktur::Component::skTransformComponent::SetScale2(const Vector2& scaleVec)
{
	m_scale = Vector3(scaleVec.x, scaleVec.y, m_scale.z);
}

Vector2 Struktur::Component::skTransformComponent::GetScale2()
{
	return Vector2(m_scale.x, m_scale.y);
}

void Struktur::Component::skTransformComponent::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skTransformComponent>("transformComponent"
		, "position", sol::property(&skTransformComponent::GetPosition2, &skTransformComponent::SetPosition2)
		, "worldPosition", sol::property(&skTransformComponent::GetWorldPosition2, &skTransformComponent::SetWorldPosition2)
		, "angle", sol::property(&skTransformComponent::GetAngle, &skTransformComponent::SetAngle)
		, "scale", sol::property(&skTransformComponent::GetScale2, &skTransformComponent::SetScale2)
	);
}
