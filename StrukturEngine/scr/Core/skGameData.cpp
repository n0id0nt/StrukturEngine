#include "skGameData.h"

void Struktur::Core::skGameData::LUABind(Util::skLuaState& lua)
{
	lua.NewUsertype<skGameData>("gameData"
		//,"registry", &skGameData::registry
		,"resourcePool", &skGameData::resourcePool
		,"world", &skGameData::world
	);
}
