#include "SpaceBlast.h"
#include "Player.h"
#include "Enemy.h"
#include "../Engine/Engine.h"

#include <iostream>
#include <vector>


using namespace std;

int main()
{
	cool::InitializeMemory();
	cool::SetFilePath("../Assets");

	//initialize engine

	cool::g_renderer.Initialize();
	cool::g_inputSystem.Initialize();
	cool::g_audioSystem.Initialize();

	//creates window
	cool::g_renderer.CreateWindow("Neumont", 800, 600);
	cool::g_renderer.setClearColor(cool::Color{ 60,60,60,255 });

	{
		//game creation
		SpaceBlast game;
		game.Initialize();

		bool quit = false;
		while (!quit)
		{
			//update (engine)
			cool::g_time.Tick();
			cool::g_inputSystem.Update();
			cool::g_audioSystem.Update();

			if (cool::g_inputSystem.GetKeyDown(cool::key_escape)) quit = true;

			game.Update();

			//renderer
			cool::g_renderer.BeginFrame();

			game.Draw(cool::g_renderer);

			cool::g_renderer.EndFrame();
		}
	}

	
	cool::g_audioSystem.Shutdown();
	cool::g_renderer.Shutdown();
}