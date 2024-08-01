#include "skLuaState.h"
#include "raylib.h"
#include <format>

Struktur::Util::skLuaState::skLuaState()
{
	m_lua = sol::state();
	m_lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);
	// Change the working directory
	//DEBUG_PRINT(Engine::GetInstance()->GetProjectDirectory());
	//m_lua.script(std::format("package.path = '{}Scripts/?.lua'", Engine::GetInstance()->GetProjectDirectory()));
	m_lua.new_usertype<skLuaState>("Script"
		//,"property", &ScriptComponent::AddScriptProperty
		,"update", &skLuaState::m_updateFunction
		//,"onCollisionEnter", &ScriptComponent::m_onCollisionEnterFunction
		//,"onCollisionExit", &ScriptComponent::m_onCollisionExitFunction
		//,"onCollisionPreSolve", &ScriptComponent::m_onCollisionPreSolveFunction
		//,"onMessage", &ScriptComponent::m_onMessage
	);
	m_lua.set("Script", this);
}

void Struktur::Util::skLuaState::Update(float dt)
{
	if (m_update.valid())
	{
		sol::protected_function updateScript = m_update;

		sol::protected_function_result result = updateScript(dt);

		// Check if the execution was successful
		if (!result.valid()) {
			// An error occurred; retrieve and handle the error message
			sol::error err = result;
			TraceLog(LOG_ERROR, std::format("Lua script execution error: {}", err.what()).c_str() );
			assert(false);
		}
	}
}

void Struktur::Util::skLuaState::ScriptFile(const std::string& filename)
{
	m_lua.script_file(filename);

	if (m_updateFunction)
	{
		m_lua.script("function update(dt) Script.update(dt) end");
		m_update = m_lua["update"];
	}
	else
	{
		TraceLog(LOG_ERROR, std::format("Lua script {} loading no Script.update() function provided", filename).c_str());
		assert(false);
	}
}

sol::table Struktur::Util::skLuaState::CreateTable()
{
	return m_lua.create_table();
}
