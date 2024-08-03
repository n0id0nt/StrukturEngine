#pragma once
#include "raylib.h"
#include "../Scripting/skLuaState.h"
#include <set>

namespace Struktur
{
	namespace Core
	{
		class skInput
		{
		private:
			struct Binding
			{
				std::set<KeyboardKey> keycodes;
				std::set<GamepadButton> controllerButtons;
			};

			struct AxisBinding
			{
				Binding positive;
				Binding negetive;
				std::set<GamepadAxis> controllerAxis;
			};

			enum class AxisComponent
			{
				Positive,
				Negetive,

				Count
			};

			struct Axis2Binding
			{
				AxisBinding xAxis;
				AxisBinding yAxis;
			};

			enum class Axis2Component
			{
				Up,
				Down,
				Left,
				Right,

				Count
			};

			enum class Axis2Direction
			{
				X,
				Y,

				Count
			};
		public:

			skInput(int gamer = 0);
			~skInput();

			void Update();

			void LoadInputBindings(const std::string& fileDir, const std::string& bindingFile);

			bool isKeyDown(KeyboardKey key);
			bool isKeyJustPressed(KeyboardKey key);
			bool isKeyJustReleased(KeyboardKey key);

			bool isControllerButtonDown(GamepadButton button);
			bool isControllerButtonJustPressed(GamepadButton button);
			bool isControllerButtonJustReleased(GamepadButton button);

			float getControllerAxisValue(GamepadAxis code);

			bool isStringKeyDown(const std::string& input);
			bool isStringKeyJustPressed(const std::string& input);
			bool isStringKeyJustReleased(const std::string& input);

			bool isStringControllerButtonDown(const std::string& input);
			bool isStringControllerButtonJustPressed(const std::string& input);
			bool isStringControllerButtonJustReleased(const std::string& input);

			float getStringControllerAxisValue(const std::string& input);

			void CreateButtonBinding(const std::string& input, KeyboardKey code);
			void CreateButtonBinding(const std::string& input, GamepadButton code);

			void CreateVairableBinding(const std::string& input, KeyboardKey code);
			void CreateVairableBinding(const std::string& input, GamepadButton code);
			void CreateVairableBinding(const std::string& input, GamepadAxis code);

			void CreateAxisBinding(const std::string& input, KeyboardKey code, AxisComponent axis);
			void CreateAxisBinding(const std::string& input, GamepadButton code, AxisComponent axis);
			void CreateAxisBinding(const std::string& input, GamepadAxis code);

			void CreateAxis2Binding(const std::string& input, KeyboardKey code, Axis2Component axis);
			void CreateAxis2Binding(const std::string& input, GamepadButton code, Axis2Component axis);
			void CreateAxis2Binding(const std::string& input, GamepadAxis code, Axis2Direction axis);

			bool isInputDown(const std::string& input);
			bool isInputJustPressed(const std::string& input);
			bool isInputJustReleased(const std::string& input);
			float getInputVariable(const std::string& input);
			float getInputAxis(const std::string& input);
			Vector2 getInputAxis2(const std::string& input);

			KeyboardKey GetKeycodeFromString(const std::string& input);
			GamepadButton GetControllerButtonFromString(const std::string& input);
			GamepadAxis GetControllerAxisFromString(const std::string& input);

			static void LUABind(Scripting::skLuaState& lua);

		private:
			std::unordered_map<std::string, Binding> m_buttonBindings;
			std::unordered_map<std::string, Binding> m_variableBindings;
			std::unordered_map<std::string, AxisBinding> m_axisBindings;
			std::unordered_map<std::string, Axis2Binding> m_axis2Bindings;
			static std::unordered_map<std::string, KeyboardKey> s_keycodeMap;
			static std::unordered_map<std::string, GamepadButton> s_controllerButtonMap;
			static std::unordered_map<std::string, GamepadAxis> s_controllerAxisMap;

			float m_deadzone;

			std::string m_gamepadId;
			int m_gamepadIndex;
		};
	};
};