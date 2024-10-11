#include "skLuaState.h"
#include "raylib.h"
#include <format>

void Struktur::Scripting::skLuaState::CreateLuaState(const std::string& workingDirectory)
{
	m_lua = sol::state();
	m_lua.collect_garbage();
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

void Struktur::Scripting::skLuaState::Initialise(float systemTime)
{
	if (m_initialise.valid())
	{
		sol::protected_function initialiseScript = m_initialise;

		sol::protected_function_result result = initialiseScript(systemTime);

		// Check if the execution was successful
		if (!result.valid()) {
			// An error occurred; retrieve and handle the error message
			sol::error err = result;
			TraceLog(LOG_ERROR, std::format("Lua script execution error: {}", err.what()).c_str());
			assert(false);
		}
	}
}

void Struktur::Scripting::skLuaState::Update(float dt, float systemTime)
{
	if (m_update.valid())
	{
		sol::protected_function updateScript = m_update;

		sol::protected_function_result result = updateScript(dt, systemTime);

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
		m_lua.script("function update(dt, systemTime) Script.update(dt, systemTime) end");
		m_update = m_lua["update"];
	}
	else
	{
		TraceLog(LOG_ERROR, std::format("Lua script {} loading no Script.update(dt, systemTime) function provided", filename).c_str());
		assert(false);
	}

	if (m_initialiseFunction)
	{
		m_lua.script("function initialise(systemTime) Script.initialise(systemTime) end");
		m_initialise = m_lua["initialise"];
	}
	else
	{
		TraceLog(LOG_ERROR, std::format("Lua script {} loading no Script.initialise(systemTime) function provided", filename).c_str());
		assert(false);
	}
}

void Struktur::Scripting::skLuaState::GarbageCollection()
{
	m_lua.collect_garbage();
}

sol::table Struktur::Scripting::skLuaState::CreateTable()
{
	return m_lua.create_table();
}
