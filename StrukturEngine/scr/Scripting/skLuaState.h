#pragma once
#include <sol/sol.hpp>
#include <functional>
#include <string>
#include <string_view>

namespace Struktur
{
	namespace Scripting
	{
		class skLuaState
		{
		public:
			skLuaState() = default;
			~skLuaState() = default;

			void CreateLuaState(const std::string& workingDirectory);
			void Initialise(float systemTime);
			void Update(float dt, float systemTime);

			void ScriptFile(const std::string& filename);

			template <typename... Args>
			void Set(Args&&... args)
			{
				m_lua.set(std::forward<Args>(args)...);
			}

			template <typename Class, typename... Args>
			void NewUsertype(Args&&... args) {
				m_lua.new_usertype<Class>(std::forward<Args>(args)...);
			}

			template <bool read_only = true, typename... Args>
			void NewEnum(const std::string_view& name, Args&&... args) {
				m_lua.new_enum<read_only>(name, std::forward<Args>(args)...);
			}

			template <typename T>
			sol::table_proxy<sol::global_table&, sol::detail::proxy_key_t<T>> operator[](T&& key) {
				return m_lua[std::forward<T>(key)];
			}

			template <typename T>
			sol::table_proxy<const sol::global_table&, sol::detail::proxy_key_t<T>> operator[](T&& key) const {
				return m_lua[std::forward<T>(key)];
			}

			sol::table CreateTable();
		private:
			sol::state m_lua;

			sol::protected_function m_update;
			std::function<void(float, float)> m_updateFunction;

			sol::protected_function m_initialise;
			std::function<void(float)> m_initialiseFunction;

			//sol::protected_function m_onMessage;
			//std::function<void(const std::string&, const sol::object&, const Entity&)> m_onMessageFunction;
		};
	};
};

