#pragma once
#include "Math/Random.h"
#include "Math/MathUtils.h"

#include "Core/Memory.h"
#include "Core//File.h"
#include "Core/Time.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"


#include <memory>


namespace cool
{
	extern InputSystem g_inputSystem;
	extern Time g_time;
	extern Renderer g_renderer;
	extern AudioSystem g_audioSystem;
}