#include "skUISystem.h"
#include "../../Core/skResourcePool.h"
#include "raygui.h"
#include "raylib.h"

void Struktur::System::UI::Update(entt::registry& registry, const Core::skResourcePool& resourcePool)
{
	// this makes a good title
	int width = GetScreenWidth();
	int height = GetScreenHeight();
	const char* name = "Bert";
	const char* paragraph = "this is the text thats \ngoing to be the paragraph so \nall my text will go here";
	int panelWidth = 400;
	int panelHeight = 150;
	int panelPadding = 30;
	DrawRectangle(width/2 - panelWidth/2 - panelPadding/2, height - panelHeight - panelPadding/2 - 80, panelWidth + panelPadding, panelHeight + panelPadding, Color{203, 219, 252, 255});
	GuiGroupBox(Rectangle{(float)width / 2.0f - panelWidth / 2.0f, height - panelHeight - 80.0f, (float)panelWidth, (float)panelHeight }, name);
	DrawText(paragraph, width / 2 - panelWidth / 2 + panelPadding / 2, height - panelHeight + panelPadding / 2 - 80.0f, 20, BLACK);
}
