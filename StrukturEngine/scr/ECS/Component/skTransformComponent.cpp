#include "skTransformComponent.h"

void Struktur::Component::skTransformComponent::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skTransformComponent>("transformComponent"
		, "translation", &skTransformComponent::translation
	);
}

Matrix Struktur::Component::skTransformComponent::ToMatrix(const Transform& transform)
{
	Vector3 x = Vector3{ transform.rotation.x, 0, 0 };
	Vector3 y = Vector3{ 0, transform.rotation.y, 0 };
	Vector3 z = Vector3{ 0, 0, transform.rotation.z };

	x = Vector3{ x.x * transform.scale.x, x.y * transform.scale.x, x.z * transform.scale.x };
	y = Vector3{ y.x * transform.scale.x, y.y * transform.scale.x, y.z * transform.scale.x };
	z = Vector3{ z.x * transform.scale.x, z.y * transform.scale.x, z.z * transform.scale.x };

	Vector3 t = transform.translation;

	return Matrix{
		x.x,x.y,x.z,0,
		y.x,y.y,y.z,0,
		z.x,z.y,z.z,0,
		t.x,t.y,t.z,0,
	};
}
