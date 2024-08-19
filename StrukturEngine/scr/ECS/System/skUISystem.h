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
			void Update(entt::registry& registry, const Core::skResourcePool& resourcePool, const skDialogueText& dialogueText, float systemTime);
		};
	};
};
