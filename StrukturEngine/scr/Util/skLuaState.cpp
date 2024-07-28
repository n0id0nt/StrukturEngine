#include "skLuaState.h"
#include "raylib.h"
#include <format>

void Struktur::Util::skLuaState::Update(float dt)
{
	if (m_update.valid())
	{
		sol::protected_function updateScript = m_update;

		sol::protected_function_result result = updateScript();

		// Check if the execution was successful
		if (!result.valid()) {
			// An error occurred; retrieve and handle the error message
			sol::error err = result;
			TraceLog(LOG_ERROR, std::format("Lua script execution error: {}", err.what()).c_str());
			assert(false);
		}
	}
}

void Struktur::Util::skLuaState::ScriptFile(const std::string& filename)
{
	m_lua.script_file(filename);

	if (m_updateFunction)
	{
		m_lua.script("function update() Script.update() end");
		m_update = m_lua["update"];
	}
	else
	{
		TraceLog(LOG_ERROR, std::format("Lua script {} loading no Script.update() function provided", filename).c_str());
		assert(false);
	}
}
