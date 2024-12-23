#pragma once
#include "Game/skLevel.h"
#include <string>

namespace Struktur
{
	namespace Component
	{
		struct skLevelComponent
		{
			std::string levelId;
			bool doNotUnload;
		};
	};
};

