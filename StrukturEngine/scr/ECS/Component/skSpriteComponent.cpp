#include "skSpriteComponent.h"

void Struktur::Component::skSpriteComponent::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skSpriteComponent>("spriteComponent"
		, "imagePath", &skSpriteComponent::imagePath
		, "size", &skSpriteComponent::size
		, "sourceRec", &skSpriteComponent::sourceRec
	);
}
