#pragma once
#include <cstdint>
#include "../Math/Vector2.h"
#include <array>
#include <vector>

namespace cool
{
	class InputSystem
	{
	public:
		enum State
		{
			Idle,
			Pressed,
			Held,
			Released
		};


	public:
		InputSystem() = default;
		~InputSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		State GetKeyState(uint32_t key);
		bool GetKeyDown(uint32_t key) { return m_keyboardState[key]; }
		bool GetPreviousKeyDown(uint32_t key) { return m_prevKeyboardState[key]; }

		const Vector2& GetMousePosition() const { return m_mousePosition; }

		State GetButtonState(uint32_t button);
		bool GetButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetPreviousButtonDown(uint32_t button) {
			return m_prevMouseButtonState[button];
		}

	private:
		int m_numKeys;
		Vector2 m_mousePosition;
		
		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;
		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;
	};

	inline InputSystem::State InputSystem::GetKeyState(uint32_t key)
	{
		State keyState = State::Idle;

		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);

		if (!keyDown && !prevKeyDown) { keyState = Idle; }
		if (keyDown && !prevKeyDown) { keyState = Pressed; }
		if (keyDown && prevKeyDown) { keyState = Held; }
		if (!keyDown && prevKeyDown) { keyState = Released; }

		return keyState;
	}

	inline InputSystem::State InputSystem::GetButtonState(uint32_t button)
	{
		State keyState = State::Idle;
		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		if (!buttonDown && !prevButtonDown) { keyState = Idle; }
		if (buttonDown && !prevButtonDown) { keyState = Pressed; }
			if (buttonDown && prevButtonDown) { keyState = Held; }
		if (!buttonDown && prevButtonDown) { keyState = Released; }

		return keyState;
	}

	extern const uint32_t key_space;
	extern const uint32_t key_up;
	extern const uint32_t key_down;
	extern const uint32_t key_left;
	extern const uint32_t key_right;
	extern const uint32_t key_escape;

	extern const uint32_t button_left;
	extern const uint32_t button_middle;
	extern const uint32_t button_right;
}