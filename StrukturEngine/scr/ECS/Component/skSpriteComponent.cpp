#include "skSpriteComponent.h"

void Struktur::Component::skSpriteComponent::SetSpriteIndex(int a_index)
{
	index = a_index;
	size = Vector2(imageWidth/columns, imageHeight/rows);
	int x = (index % columns) * size.x;
	int y = std::floor(index / columns) * size.y;

	sourceRec = Rectangle{ (float)x, (float)y, size.x, size.y };

	if (flipped)
	{
		sourceRec.width *= -1;
	}
}

void Struktur::Component::skSpriteComponent::SetImage(const std::string& a_imagePath, int a_rows, int a_columns, int a_index, const Struktur::Core::skResourcePool& resourcePool)
{
	imagePath = a_imagePath;
	rows = a_rows;
	columns = a_columns;
	const Image& image = resourcePool.RetrieveImage(a_imagePath);
	imageWidth = image.width;
	imageHeight = image.height;
	SetSpriteIndex(a_index);
}

void Struktur::Component::skSpriteComponent::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skSpriteComponent>("spriteComponent"
		, "imagePath", &skSpriteComponent::imagePath
		, "size", &skSpriteComponent::size
		, "offset", &skSpriteComponent::offset
		, "sourceRec", &skSpriteComponent::sourceRec
		, "columns", &skSpriteComponent::columns
		, "rows", &skSpriteComponent::rows
		, "imageWidth", &skSpriteComponent::imageWidth
		, "imageHeight", &skSpriteComponent::imageHeight
		, "flipped", &skSpriteComponent::flipped
		, "index", &skSpriteComponent::index
		, "setImage", &skSpriteComponent::SetImage
		, "setSpriteIndex", &skSpriteComponent::SetSpriteIndex
	);
}
