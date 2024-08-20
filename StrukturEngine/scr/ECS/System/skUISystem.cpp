#include "skUISystem.h"
#include "../../Core/skResourcePool.h"
#include "raygui.h"
#include "raylib.h"

void Struktur::System::UI::Update(entt::registry& registry, const Core::skResourcePool& resourcePool, const skDialogueText& dialogueText, float systemTime, skGameState& out_gameState, skGameState& out_prevGameState, bool& out_closeWindow)
{
	switch (out_gameState)
	{
	case skGameState::MAIN_MENU:
	{
		// this makes a good title
		int width = GetScreenWidth();
		int height = GetScreenHeight();
		int panelWidth = 150;
		int panelHeight = 30;
		int panelPadding = 30;
		DrawRectangle(0, 0, width, height, Color{ 5, 5, 5, 100 });
		const char* gameTitle = "Growtesque";
		int fontSize = 50;
		int textWidth = MeasureText(gameTitle, fontSize);
		DrawText(gameTitle, width / 2 - textWidth / 2, height - textWidth / 2 - 280.0f, fontSize, Color{102, 57, 49, 255});
		int result = GuiButton(Rectangle{ (float)width / 2.0f - panelWidth / 2.0f, height - panelHeight - 180.0f, (float)panelWidth, (float)panelHeight }, "Play Game");
		out_closeWindow |= GuiButton(Rectangle{ (float)width / 2.0f - panelWidth / 2.0f, height - panelHeight - 80.0f, (float)panelWidth, (float)panelHeight }, "Quit");
		if (result)
		{
			out_gameState = skGameState::CUT_SCENE;
		}
		
		break;
	}
	case skGameState::PAUSE:
	{
		// this makes a good title
		int width = GetScreenWidth();
		int height = GetScreenHeight();
		int panelWidth = 150;
		int panelHeight = 30;
		int panelPadding = 30;
		DrawRectangle(0, 0, width, height, Color{ 5, 5, 5, 200 });
		const char* gameTitle = "Paused";
		int fontSize = 50;
		int textWidth = MeasureText(gameTitle, fontSize);
		DrawText(gameTitle, width / 2 - textWidth / 2, height - textWidth / 2 - 280.0f, fontSize, Color{ 102, 57, 49, 255 });
		int result = GuiButton(Rectangle{ (float)width / 2.0f - panelWidth / 2.0f, height - panelHeight - 180.0f, (float)panelWidth, (float)panelHeight }, "Resume");
		out_closeWindow |= GuiButton(Rectangle{ (float)width / 2.0f - panelWidth / 2.0f, height - panelHeight - 80.0f, (float)panelWidth, (float)panelHeight }, "Quit");
		if (result)
		{
			out_gameState = out_prevGameState;
			out_prevGameState = skGameState::PAUSE;
		}
		break;
	}
	case skGameState::CUT_SCENE:
	{
		if (dialogueText.dialogueVisible)
		{
			// this makes a good title
			int width = GetScreenWidth();
			int height = GetScreenHeight();
			int panelWidth = 400;
			int panelHeight = 150;
			int panelPadding = 30;
			DrawRectangle(width / 2 - panelWidth / 2 - panelPadding / 2, height - panelHeight - panelPadding / 2 - 40, panelWidth + panelPadding, panelHeight + panelPadding, Color{ 203, 219, 252, 255 });
			GuiGroupBox(Rectangle{ (float)width / 2.0f - panelWidth / 2.0f, height - panelHeight - 40.0f, (float)panelWidth, (float)panelHeight }, dialogueText.name.c_str());
			DrawText(dialogueText.paragraph.c_str(), width / 2 - panelWidth / 2 + panelPadding / 2, height - panelHeight + panelPadding / 2 - 40.0f, 20, BLACK);
		}
		break;
	}
	case skGameState::GAME:
	{
		break;
	}
	default:
		break;
	}

}
