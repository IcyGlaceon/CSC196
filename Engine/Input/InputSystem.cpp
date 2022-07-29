#include "InputSystem.h"
#include <SDL.h>
#include <iostream>


namespace cool 
{
	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_up = SDL_SCANCODE_UP;
	const uint32_t key_down = SDL_SCANCODE_DOWN;
	const uint32_t key_left = SDL_SCANCODE_LEFT;
	const uint32_t key_right = SDL_SCANCODE_RIGHT;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;

	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;

	


	void cool::InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		
		m_keyboardState.resize(m_numKeys);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevKeyboardState = m_keyboardState;
	}

	void cool::InputSystem::Shutdown()
	{
		//
	}

	void cool::InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		//save previous keyboard state
		m_prevKeyboardState = m_keyboardState;

		//get current keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());


		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);

		m_mousePosition = cool::Vector2{ x , y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK;  
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; 
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK;

	}

	

}
