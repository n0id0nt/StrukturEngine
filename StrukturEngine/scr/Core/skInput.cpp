#include "skInput.h"
#include "pugixml.hpp"
#include <format>

std::unordered_map<std::string, KeyboardKey> Struktur::Core::skInput::s_keycodeMap = {
	{"null",				KEY_NULL},
	// Alphanumeric keys
	{"apostrophe",          KEY_APOSTROPHE},
	{"comma",               KEY_COMMA},
	{"minus",               KEY_MINUS},
	{"period",              KEY_PERIOD},
	{"slash",				KEY_SLASH},
	{"0",					KEY_ZERO},
	{"1",					KEY_ONE},
	{"2",					KEY_TWO},
	{"3",					KEY_THREE},
	{"4",					KEY_FOUR},
	{"5",					KEY_FIVE},
	{"6",					KEY_SIX},
	{"7",					KEY_SEVEN},
	{"8",					KEY_EIGHT},
	{"9",					KEY_NINE},
	{"semicolon",           KEY_SEMICOLON},
	{"equal",				KEY_EQUAL},
	{"a",					KEY_A},
	{"b",                   KEY_B},
	{"c",                   KEY_C},
	{"d",                   KEY_D},
	{"e",                   KEY_E},
	{"f",                   KEY_F},
	{"g",                   KEY_G},
	{"h",                   KEY_H},
	{"i",                   KEY_I},
	{"j",                   KEY_J},
	{"k",                   KEY_K},
	{"l",					KEY_L},
	{"m",					KEY_M},
	{"n",					KEY_N},
	{"o",					KEY_O},
	{"p",					KEY_P},
	{"q",					KEY_Q},
	{"r",					KEY_R},
	{"s",					KEY_S},
	{"t",					KEY_T},
	{"u",					KEY_U},
	{"v",					KEY_V},
	{"w",					KEY_W},
	{"x",					KEY_X},
	{"y",                   KEY_Y},
	{"z",                   KEY_Z},
	{"leftbracket",         KEY_LEFT_BRACKET},
	{"backspace",           KEY_BACKSLASH},
	{"rightbracket",        KEY_RIGHT_BRACKET},
	{"grave",               KEY_GRAVE},
	// Function keys
	{"space",               KEY_SPACE},
	{"escape",              KEY_ESCAPE},
	{"enter",               KEY_ENTER},
	{"tab",                 KEY_TAB},
	{"backspace",           KEY_BACKSPACE},
	{"insert",              KEY_INSERT},
	{"delete",              KEY_DELETE},
	{"right",               KEY_RIGHT},
	{"left",                KEY_LEFT},
	{"down",                KEY_DOWN},
	{"up",                  KEY_UP},
	{"pageup",              KEY_PAGE_UP},
	{"pagedown",            KEY_PAGE_DOWN},
	{"home",                KEY_HOME},
	{"end",                 KEY_END},
	{"capslock",            KEY_CAPS_LOCK},
	{"scrolllock",          KEY_SCROLL_LOCK},
	{"numlock",             KEY_NUM_LOCK},
	{"printscreen",         KEY_PRINT_SCREEN},
	{"pause",				KEY_PAUSE},
	{"f1",                  KEY_F1},
	{"f2",                  KEY_F2},
	{"f3",                  KEY_F3},
	{"f4",                  KEY_F4},
	{"f5",                  KEY_F5},
	{"f6",                  KEY_F6},
	{"f7",                  KEY_F7},
	{"f8",                  KEY_F8},
	{"f9",                  KEY_F9},
	{"f10",                 KEY_F10},
	{"f11",                 KEY_F11},
	{"f12",                 KEY_F12},
	{"leftshift",			KEY_LEFT_SHIFT},
	{"leftcontrol",         KEY_LEFT_CONTROL},
	{"leftalt",             KEY_LEFT_ALT},
	{"leftsuper",           KEY_LEFT_SUPER},
	{"rightshift",          KEY_RIGHT_SHIFT},
	{"rightcontrol",        KEY_RIGHT_CONTROL},
	{"rightalt",            KEY_RIGHT_ALT},
	{"rightsuper",          KEY_RIGHT_SUPER},
	{"kbmenu",				KEY_KB_MENU},
	// Keypad keys
	{"kp0",					KEY_KP_0},
	{"kp1",					KEY_KP_1},
	{"kp2",                 KEY_KP_2},
	{"kp3",					KEY_KP_3},
	{"kp4",					KEY_KP_4},
	{"kp5",					KEY_KP_5},
	{"kp6",					KEY_KP_6},
	{"kp7",					KEY_KP_7},
	{"kp8",					KEY_KP_8},
	{"kp9",					KEY_KP_9},
	{"kpdecimal",           KEY_KP_DECIMAL},
	{"kpdivide",            KEY_KP_DIVIDE},
	{"kpmultiply",          KEY_KP_MULTIPLY},
	{"kpsubtract",          KEY_KP_SUBTRACT},
	{"kpadd",               KEY_KP_ADD},
	{"kpenter",             KEY_KP_ENTER},
	{"kpequal",             KEY_KP_EQUAL},
	// Android key buttons
	{"anback",              KEY_BACK},
	{"anmenu",              KEY_MENU},
	{"anvolumeup",          KEY_VOLUME_UP},
	{"anvolumedown",        KEY_VOLUME_DOWN},
};

std::unordered_map<std::string, GamepadButton> Struktur::Core::skInput::s_controllerButtonMap = {
	{"unknown",     GAMEPAD_BUTTON_UNKNOWN},
	{"a",           GAMEPAD_BUTTON_RIGHT_FACE_DOWN},
	{"b",           GAMEPAD_BUTTON_RIGHT_FACE_LEFT},
	{"x",           GAMEPAD_BUTTON_RIGHT_FACE_RIGHT},
	{"y",           GAMEPAD_BUTTON_RIGHT_FACE_UP},
	{"select",      GAMEPAD_BUTTON_MIDDLE_LEFT},
	{"guide",       GAMEPAD_BUTTON_MIDDLE},
	{"start",       GAMEPAD_BUTTON_MIDDLE_RIGHT},
	{"ljoystick",   GAMEPAD_BUTTON_LEFT_THUMB},
	{"rjoystick",   GAMEPAD_BUTTON_RIGHT_THUMB},
	{"ltrigger",    GAMEPAD_BUTTON_LEFT_TRIGGER_1},
	{"lbumper",     GAMEPAD_BUTTON_LEFT_TRIGGER_2},
	{"rtrigger",    GAMEPAD_BUTTON_RIGHT_TRIGGER_1},
	{"rbumper",     GAMEPAD_BUTTON_RIGHT_TRIGGER_2},
	{"up",          GAMEPAD_BUTTON_LEFT_FACE_UP},
	{"down",        GAMEPAD_BUTTON_LEFT_FACE_DOWN},
	{"left",        GAMEPAD_BUTTON_LEFT_FACE_LEFT},
	{"right",       GAMEPAD_BUTTON_LEFT_FACE_RIGHT},
};

std::unordered_map<std::string, GamepadAxis> Struktur::Core::skInput::s_controllerAxisMap = {
	{"leftx",       GAMEPAD_AXIS_LEFT_X},
	{"lefty",       GAMEPAD_AXIS_LEFT_Y},
	{"rightx",      GAMEPAD_AXIS_RIGHT_X},
	{"rightx",      GAMEPAD_AXIS_RIGHT_Y},
	{"lefttrigger", GAMEPAD_AXIS_LEFT_TRIGGER},
	{"rightTrigger",GAMEPAD_AXIS_RIGHT_TRIGGER},
};

Struktur::Core::skInput::skInput(int gamer) : m_buttonBindings(), m_variableBindings(), m_axisBindings(), m_axis2Bindings(), m_deadzone(), m_gamepadIndex(gamer)
{
	// check the controller is connected
	if (IsGamepadAvailable(m_gamepadIndex))
	{
		m_gamepadId = GetGamepadName(m_gamepadIndex);
	}
	else
	{
		TraceLog(LOG_WARNING, std::format("gamepad {} is not connected.", m_gamepadIndex).c_str());
	}
}

Struktur::Core::skInput::~skInput()
{
	// clean up the controller
}

void Struktur::Core::skInput::Update()
{
	// checks if the controller is still available
	if (IsGamepadAvailable(m_gamepadIndex))
	{
		m_gamepadId = GetGamepadName(m_gamepadIndex);
	}
}

void Struktur::Core::skInput::LoadInputBindings(const std::string& fileDir, const std::string& bindingFile)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file((fileDir + bindingFile).c_str());
	assert(result);

	auto controllerAxis = doc.child("controllerAxis");

	m_deadzone = controllerAxis.attribute("deadzone").as_float();

	for (auto& input : doc.child("inputs").children())
	{
		std::string name(input.attribute("name").as_string());
		std::string inputType(input.attribute("type").as_string());
		if (inputType == "button")
		{
			for (auto& binding : input.child("bindings").children())
			{
				std::string bindingType(binding.attribute("type").as_string());
				std::string value(binding.attribute("value").as_string());
				if (bindingType == "keycode")
				{
					CreateButtonBinding(name, GetKeycodeFromString(value));
				}
				else if (bindingType == "controllerButton")
				{
					CreateButtonBinding(name, GetControllerButtonFromString(value));
				}
				else
				{
					TraceLog(LOG_ERROR, std::format("{} is not a valid binding type.", bindingType).c_str());
					assert(false);
				}
			}
		}
		else if (inputType == "variable")
		{
			for (auto& binding : input.child("bindings").children())
			{
				std::string bindingType(binding.attribute("type").as_string());
				std::string value(binding.attribute("value").as_string());
				if (bindingType == "keycode")
				{
					CreateVairableBinding(name, GetKeycodeFromString(value));
				}
				else if (bindingType == "controllerButton")
				{
					CreateVairableBinding(name, GetControllerButtonFromString(value));
				}
				else
				{
					TraceLog(LOG_ERROR, std::format("{} is not a valid binding type.", bindingType).c_str());
					assert(false);
				}
			}
		}
		else if (inputType == "axis")
		{
			for (auto& binding : input.child("bindings").children())
			{
				std::string bindingType(binding.attribute("type").as_string());
				std::string value(binding.attribute("value").as_string());
				std::string component(binding.attribute("component").as_string());

				if (bindingType == "keycode")
				{
					//TODO convert this to a function
					AxisComponent axis;
					if (component == "positive")
						axis = AxisComponent::Positive;
					else if (component == "negetive")
						axis = AxisComponent::Negetive;
					else
						assert(false);
					CreateAxisBinding(name, GetKeycodeFromString(value), axis);
				}
				else if (bindingType == "controllerButton")
				{
					AxisComponent axis;
					if (component == "positive")
						axis = AxisComponent::Positive;
					else if (component == "negetive")
						axis = AxisComponent::Negetive;
					else
						assert(false);
					CreateAxisBinding(name, GetControllerButtonFromString(value), axis);
				}
				else if (bindingType == "controllerAxis")
				{
					CreateAxisBinding(name, GetControllerAxisFromString(value));
				}
				else
				{
					TraceLog(LOG_ERROR, std::format("{} is not a valid binding type.", bindingType).c_str());
					assert(false);
				}
			}
		}
		else if (inputType == "axis2")
		{
			for (auto& binding : input.child("bindings").children())
			{
				std::string bindingType(binding.attribute("type").as_string());
				std::string value(binding.attribute("value").as_string());
				std::string component(binding.attribute("component").as_string());

				Axis2Component axis;
				if (component == "up")
					axis = Axis2Component::Up;
				else if (component == "down")
					axis = Axis2Component::Down;
				else if (component == "left")
					axis = Axis2Component::Left;
				else if (component == "right")
					axis = Axis2Component::Right;
				else
					assert(false);

				if (bindingType == "keycode")
				{
					CreateAxis2Binding(name, GetKeycodeFromString(value), axis);
				}
				else if (bindingType == "controllerButton")
				{
					CreateAxis2Binding(name, GetControllerButtonFromString(value), axis);
				}
				else
				{
					TraceLog(LOG_ERROR, std::format("{} is not a valid binding type.", bindingType).c_str());
					assert(false);
				}
			}
		}
		else
		{
			TraceLog(LOG_ERROR, std::format("{} is not a valid input type.", inputType).c_str());
			assert(false);
		}
	}
}

bool Struktur::Core::skInput::isKeyDown(KeyboardKey key)
{
	return IsKeyDown(key);
}

bool Struktur::Core::skInput::isKeyJustPressed(KeyboardKey key)
{
	return IsKeyPressed(key);
}

bool Struktur::Core::skInput::isKeyJustReleased(KeyboardKey key)
{
	return IsKeyReleased(key);
}

bool Struktur::Core::skInput::isControllerButtonDown(GamepadButton button)
{
	return IsGamepadButtonDown(m_gamepadIndex, button);
}

bool Struktur::Core::skInput::isControllerButtonJustPressed(GamepadButton button)
{
	return IsGamepadButtonPressed(m_gamepadIndex, button);
}

bool Struktur::Core::skInput::isControllerButtonJustReleased(GamepadButton button)
{
	return IsGamepadButtonReleased(m_gamepadIndex, button);
}

float Struktur::Core::skInput::getControllerAxisValue(GamepadAxis code)
{
	return GetGamepadAxisMovement(m_gamepadIndex, code);
}

bool Struktur::Core::skInput::isStringKeyDown(const std::string& input)
{
	KeyboardKey key = GetKeycodeFromString(input);
	return isKeyDown(key);
}

bool Struktur::Core::skInput::isStringKeyJustPressed(const std::string& input)
{
	KeyboardKey key = GetKeycodeFromString(input);
	return isKeyJustPressed(key);
}

bool Struktur::Core::skInput::isStringKeyJustReleased(const std::string& input)
{
	KeyboardKey key = GetKeycodeFromString(input);
	return isKeyJustReleased(key);
}

bool Struktur::Core::skInput::isStringControllerButtonDown(const std::string& input)
{
	GamepadButton key = GetControllerButtonFromString(input);
	return isControllerButtonDown(key);
}

bool Struktur::Core::skInput::isStringControllerButtonJustPressed(const std::string& input)
{
	GamepadButton key = GetControllerButtonFromString(input);
	return isControllerButtonJustPressed(key);
}

bool Struktur::Core::skInput::isStringControllerButtonJustReleased(const std::string& input)
{
	GamepadButton key = GetControllerButtonFromString(input);
	return isControllerButtonJustReleased(key);
}

float Struktur::Core::skInput::getStringControllerAxisValue(const std::string& input)
{
	GamepadAxis key = GetControllerAxisFromString(input);
	return getControllerAxisValue(key);
}

void Struktur::Core::skInput::CreateButtonBinding(const std::string& input, KeyboardKey code)
{
	auto it = m_buttonBindings.find(input);
	if (it == m_buttonBindings.end())
		m_buttonBindings[input].keycodes = std::set{ code };
	else
		m_buttonBindings[input].keycodes.insert(code);
}

void Struktur::Core::skInput::CreateButtonBinding(const std::string& input, GamepadButton code)
{
	auto it = m_buttonBindings.find(input);
	if (it == m_buttonBindings.end())
		m_buttonBindings[input].controllerButtons = std::set{ code };
	else
		m_buttonBindings[input].controllerButtons.insert(code);
}

void Struktur::Core::skInput::CreateVairableBinding(const std::string& input, KeyboardKey code)
{
	auto it = m_variableBindings.find(input);
	if (it == m_variableBindings.end())
		m_variableBindings[input].keycodes = std::set{ code };
	else
		m_variableBindings[input].keycodes.insert(code);
}

void Struktur::Core::skInput::CreateVairableBinding(const std::string& input, GamepadButton code)
{
	auto it = m_variableBindings.find(input);
	if (it == m_variableBindings.end())
		m_variableBindings[input].controllerButtons = std::set{ code };
	else
		m_variableBindings[input].controllerButtons.insert(code);
}

void Struktur::Core::skInput::CreateAxisBinding(const std::string& input, KeyboardKey code, AxisComponent axis)
{
	auto it = m_axisBindings.find(input);
	bool hasBinding = it == m_axisBindings.end();
	switch (axis)
	{
	case AxisComponent::Positive:
		if (hasBinding)
			m_axisBindings[input].positive.keycodes = std::set{ code };
		else
			m_axisBindings[input].positive.keycodes.insert(code);
		break;
	case AxisComponent::Negetive:
		if (hasBinding)
			m_axisBindings[input].negetive.keycodes = std::set{ code };
		else
			m_axisBindings[input].negetive.keycodes.insert(code);
		break;
	default:
		assert(false);
	}
}

void Struktur::Core::skInput::CreateAxisBinding(const std::string& input, GamepadButton code, AxisComponent axis)
{
	auto it = m_axisBindings.find(input);
	bool hasBinding = it == m_axisBindings.end();
	switch (axis)
	{
	case AxisComponent::Positive:
		if (hasBinding)
			m_axisBindings[input].positive.controllerButtons = std::set{ code };
		else
			m_axisBindings[input].positive.controllerButtons.insert(code);
		break;
	case AxisComponent::Negetive:
		if (hasBinding)
			m_axisBindings[input].negetive.controllerButtons = std::set{ code };
		else
			m_axisBindings[input].negetive.controllerButtons.insert(code);
		break;
	default:
		assert(false);
	}
}

void Struktur::Core::skInput::CreateAxisBinding(const std::string& input, GamepadAxis code)
{
	auto it = m_axisBindings.find(input);
	if (it == m_axisBindings.end())
		m_axisBindings[input].controllerAxis = std::set{ code };
	else
		m_axisBindings[input].controllerAxis.insert(code);
}

void Struktur::Core::skInput::CreateAxis2Binding(const std::string& input, KeyboardKey code, Axis2Component axis)
{
	auto it = m_axis2Bindings.find(input);
	bool hasBinding = it == m_axis2Bindings.end();
	switch (axis)
	{
	case Axis2Component::Up:
		if (hasBinding)
			m_axis2Bindings[input].yAxis.positive.keycodes = std::set{ code };
		else
			m_axis2Bindings[input].yAxis.positive.keycodes.insert(code);
		break;
	case Axis2Component::Down:
		if (hasBinding)
			m_axis2Bindings[input].yAxis.negetive.keycodes = std::set{ code };
		else
			m_axis2Bindings[input].yAxis.negetive.keycodes.insert(code);
		break;
	case Axis2Component::Left:
		if (hasBinding)
			m_axis2Bindings[input].xAxis.negetive.keycodes = std::set{ code };
		else
			m_axis2Bindings[input].xAxis.negetive.keycodes.insert(code);
		break;
	case Axis2Component::Right:
		if (hasBinding)
			m_axis2Bindings[input].xAxis.positive.keycodes = std::set{ code };
		else
			m_axis2Bindings[input].xAxis.positive.keycodes.insert(code);
		break;
	default:
		assert(false);
	}
}

void Struktur::Core::skInput::CreateAxis2Binding(const std::string& input, GamepadButton code, Axis2Component axis)
{
	auto it = m_axis2Bindings.find(input);
	bool hasBinding = it == m_axis2Bindings.end();
	switch (axis)
	{
	case Axis2Component::Up:
		if (hasBinding)
			m_axis2Bindings[input].yAxis.positive.controllerButtons = std::set{ code };
		else
			m_axis2Bindings[input].yAxis.positive.controllerButtons.insert(code);
		break;
	case Axis2Component::Down:
		if (hasBinding)
			m_axis2Bindings[input].yAxis.negetive.controllerButtons = std::set{ code };
		else
			m_axis2Bindings[input].yAxis.negetive.controllerButtons.insert(code);
		break;
	case Axis2Component::Left:
		if (hasBinding)
			m_axis2Bindings[input].xAxis.negetive.controllerButtons = std::set{ code };
		else
			m_axis2Bindings[input].xAxis.negetive.controllerButtons.insert(code);
		break;
	case Axis2Component::Right:
		if (hasBinding)
			m_axis2Bindings[input].xAxis.positive.controllerButtons = std::set{ code };
		else
			m_axis2Bindings[input].xAxis.positive.controllerButtons.insert(code);
		break;
	default:
		assert(false);
	}
}

void Struktur::Core::skInput::CreateAxis2Binding(const std::string& input, GamepadAxis code, Axis2Direction axis)
{
	auto it = m_axis2Bindings.find(input);
	bool hasBinding = it == m_axis2Bindings.end();
	switch (axis)
	{
	case Axis2Direction::X:
		if (hasBinding)
			m_axis2Bindings[input].xAxis.controllerAxis = std::set{ code };
		else
			m_axis2Bindings[input].xAxis.controllerAxis.insert(code);
		break;
	case Axis2Direction::Y:
		if (hasBinding)
			m_axis2Bindings[input].yAxis.controllerAxis = std::set{ code };
		else
			m_axis2Bindings[input].yAxis.controllerAxis.insert(code);
		break;
	default:
		assert(false);
	}
}

bool Struktur::Core::skInput::isInputDown(const std::string& input)
{
	auto keys = m_buttonBindings.find(input);
	assert(keys != m_buttonBindings.end());
	for (auto it = keys->second.keycodes.begin(); it != keys->second.keycodes.end(); ++it)
	{
		if (isKeyDown(*it))
			return true;
	}
	for (auto it = keys->second.controllerButtons.begin(); it != keys->second.controllerButtons.end(); ++it)
	{
		if (isControllerButtonDown(*it))
			return true;
	}
	return false;
}

bool Struktur::Core::skInput::isInputJustPressed(const std::string& input)
{
	auto keys = m_buttonBindings.find(input);
	assert(keys != m_buttonBindings.end());
	for (auto it = keys->second.keycodes.begin(); it != keys->second.keycodes.end(); ++it)
	{
		if (isKeyJustPressed(*it))
			return true;
	}
	for (auto it = keys->second.controllerButtons.begin(); it != keys->second.controllerButtons.end(); ++it)
	{
		if (isControllerButtonJustPressed(*it))
			return true;
	}
	return false;
}

bool Struktur::Core::skInput::isInputJustReleased(const std::string& input)
{
	auto keys = m_buttonBindings.find(input);
	assert(keys != m_buttonBindings.end());
	for (auto it = keys->second.keycodes.begin(); it != keys->second.keycodes.end(); ++it)
	{
		if (isKeyJustReleased(*it))
			return true;
	}
	for (auto it = keys->second.controllerButtons.begin(); it != keys->second.controllerButtons.end(); ++it)
	{
		if (isControllerButtonJustReleased(*it))
			return true;
	}
	return false;
}

float Struktur::Core::skInput::getInputVariable(const std::string& input)
{
	auto keys = m_variableBindings.find(input);
	assert(keys != m_variableBindings.end());
	for (auto it = keys->second.keycodes.begin(); it != keys->second.keycodes.end(); ++it)
	{
		if (isKeyDown(*it))
			return 1.f;
	}
	for (auto it = keys->second.controllerButtons.begin(); it != keys->second.controllerButtons.end(); ++it)
	{
		if (isControllerButtonDown(*it))
			return 1.f;
	}
	return 0.f;
}

float Struktur::Core::skInput::getInputAxis(const std::string& input)
{
	auto keys = m_axisBindings.find(input);
	assert(keys != m_axisBindings.end());

	float positive = 0.f;
	for (auto it = keys->second.positive.keycodes.begin(); it != keys->second.positive.keycodes.end(); ++it)
	{
		if (isKeyDown(*it))
			positive = 1.f;
	}
	for (auto it = keys->second.positive.controllerButtons.begin(); it != keys->second.positive.controllerButtons.end(); ++it)
	{
		if (isControllerButtonDown(*it))
			positive = 1.f;
	}

	float negetive = 0.f;
	for (auto it = keys->second.negetive.keycodes.begin(); it != keys->second.negetive.keycodes.end(); ++it)
	{
		if (isKeyDown(*it))
			negetive = 1.f;
	}
	for (auto it = keys->second.negetive.controllerButtons.begin(); it != keys->second.negetive.controllerButtons.end(); ++it)
	{
		if (isControllerButtonDown(*it))
			negetive = 1.f;
	}

	float value = positive - negetive;

	if (!value)
	{
		for (auto it = keys->second.controllerAxis.begin(); it != keys->second.controllerAxis.end(); ++it)
		{
			value += getControllerAxisValue(*it);
		}
		value /= (float)keys->second.controllerAxis.size();
	}
	return value;
}

Vector2 Struktur::Core::skInput::getInputAxis2(const std::string& input)
{
	auto keys = m_axis2Bindings.find(input);
	assert(keys != m_axis2Bindings.end());

	float up = 0.f;
	for (auto it = keys->second.yAxis.positive.keycodes.begin(); it != keys->second.yAxis.positive.keycodes.end(); ++it)
	{
		if (isKeyDown(*it))
			up = 1.f;
	}
	for (auto it = keys->second.yAxis.positive.controllerButtons.begin(); it != keys->second.yAxis.positive.controllerButtons.end(); ++it)
	{
		if (isControllerButtonDown(*it))
			up = 1.f;
	}

	float down = 0.f;
	for (auto it = keys->second.yAxis.negetive.keycodes.begin(); it != keys->second.yAxis.negetive.keycodes.end(); ++it)
	{
		if (isKeyDown(*it))
			down = 1.f;
	}
	for (auto it = keys->second.yAxis.negetive.controllerButtons.begin(); it != keys->second.yAxis.negetive.controllerButtons.end(); ++it)
	{
		if (isControllerButtonDown(*it))
			down = 1.f;
	}

	float left = 0.f;
	for (auto it = keys->second.xAxis.negetive.keycodes.begin(); it != keys->second.xAxis.negetive.keycodes.end(); ++it)
	{
		if (isKeyDown(*it))
			left = 1.f;
	}
	for (auto it = keys->second.xAxis.negetive.controllerButtons.begin(); it != keys->second.xAxis.negetive.controllerButtons.end(); ++it)
	{
		if (isControllerButtonDown(*it))
			left = 1.f;
	}

	float right = 0.f;
	for (auto it = keys->second.xAxis.positive.keycodes.begin(); it != keys->second.xAxis.positive.keycodes.end(); ++it)
	{
		if (isKeyDown(*it))
			right = 1.f;
	}
	for (auto it = keys->second.xAxis.positive.controllerButtons.begin(); it != keys->second.xAxis.positive.controllerButtons.end(); ++it)
	{
		if (isControllerButtonDown(*it))
			right = 1.f;
	}

	return Vector2{ right - left, up - down };
}

KeyboardKey Struktur::Core::skInput::GetKeycodeFromString(const std::string& input)
{
	auto it = s_keycodeMap.find(input);
	assert(it != s_keycodeMap.end());
	return it->second;
}

GamepadButton Struktur::Core::skInput::GetControllerButtonFromString(const std::string& input)
{
	auto it = s_controllerButtonMap.find(input);
	assert(it != s_controllerButtonMap.end());
	return it->second;
}

GamepadAxis Struktur::Core::skInput::GetControllerAxisFromString(const std::string& input)
{
	auto it = s_controllerAxisMap.find(input);
	assert(it != s_controllerAxisMap.end());
	return it->second;
}

void Struktur::Core::skInput::LUABind(Scripting::skLuaState& lua)
{
	lua.NewUsertype<skInput>("input",
		"isInputDown", &skInput::isInputDown,
		"isInputJustPressed", &skInput::isInputJustPressed,
		"isInputJustReleased", &skInput::isInputJustReleased,
		"isKeyDown", &skInput::isStringKeyDown,
		"isKeyJustPressed", &skInput::isStringKeyJustPressed,
		"isKeyJustReleased", &skInput::isStringKeyJustReleased,
		"isStringControllerButtonDown", &skInput::isStringControllerButtonDown,
		"isStringControllerButtonJustPressed", &skInput::isStringControllerButtonJustPressed,
		"isStringControllerButtonJustReleased", &skInput::isStringControllerButtonJustReleased,
		"getInputVariable", &skInput::getInputVariable,
		"getInputAxis", &skInput::getInputAxis,
		"getInputAxis2", &skInput::getInputAxis2
	);
}
