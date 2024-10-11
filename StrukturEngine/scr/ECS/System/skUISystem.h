#pragma once
#include <entt/entt.hpp>
#include <string>

struct skDialogueText
{
	std::string name;
	std::string paragraph;
	float startTime;
	bool showAllText;
	bool dialogueVisible;
};

enum class skGameState
{
	MAIN_MENU,
	GAME,
	CUT_SCENE,
	PAUSE,

	COUNT

};

namespace Struktur
{
	namespace Core
	{
		class skResourcePool;
	}
	namespace System
	{
		namespace UI
		{
			void Update(entt::registry& registry, const Core::skResourcePool& resourcePool, const skDialogueText& dialogueText, float systemTime, skGameState& out_gameState, skGameState& out_prevGameState, bool& out_closeWindow);
		};
	};
};
