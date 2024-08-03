#include "skLuaState.h"
#include "raylib.h"
#include <format>

void Struktur::Scripting::skLuaState::CreateLuaState(const std::string& workingDirectory)
{
	m_lua = sol::state();
	m_lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);
	// Change the working directory
	//DEBUG_PRINT(Engine::GetInstance()->GetProjectDirectory());
	TraceLog(LOG_INFO, std::format("Lua working directory set to: {}Scripts", workingDirectory).c_str());

	m_lua.script(std::format("package.path = '{}Scripts/?.lua'", workingDirectory));
	m_lua.new_usertype<skLuaState>("Script"
		//,"property", &ScriptComponent::AddScriptProperty
		,"update", &skLuaState::m_updateFunction
		,"initialise", &skLuaState::m_initialiseFunction
		//,"onCollisionEnter", &ScriptComponent::m_onCollisionEnterFunction
		//,"onCollisionExit", &ScriptComponent::m_onCollisionExitFunction
		//,"onCollisionPreSolve", &ScriptComponent::m_onCollisionPreSolveFunction
		//,"onMessage", &ScriptComponent::m_onMessage
	);
	m_lua.set("Script", this);
}

void Struktur::Scripting::skLuaState::Initialise()
{
	if (m_initialise.valid())
	{
		sol::protected_function initialiseScript = m_initialise;

		sol::protected_function_result result = initialiseScript();

		// Check if the execution was successful
		if (!result.valid()) {
			// An error occurred; retrieve and handle the error message
			sol::error err = result;
			TraceLog(LOG_ERROR, std::format("Lua script execution error: {}", err.what()).c_str());
			assert(false);
		}
	}
}

void Struktur::Scripting::skLuaState::Update(float dt)
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

void Struktur::Scripting::skLuaState::ScriptFile(const std::string& filename)
{
	m_lua.script_file(filename);

	if (m_updateFunction)
	{
		m_lua.script("function update(dt) Script.update(dt) end");
		m_update = m_lua["update"];
	}
	else
	{
		TraceLog(LOG_ERROR, std::format("Lua script {} loading no Script.update(dt) function provided", filename).c_str());
		assert(false);
	}

	if (m_initialiseFunction)
	{
		m_lua.script("function initialise() Script.initialise() end");
		m_initialise = m_lua["initialise"];
	}
	else
	{
		TraceLog(LOG_ERROR, std::format("Lua script {} loading no Script.initialise() function provided", filename).c_str());
		assert(false);
	}
}

sol::table Struktur::Scripting::skLuaState::CreateTable()
{
	return m_lua.create_table();
}
