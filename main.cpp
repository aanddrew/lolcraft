#include "stage3/stage3.h"
#include "hud/include/MainMenu.h"

int main()
{
	s3::Window window("lolcraft", 1600, 900);

	s3::Shader hudShader("res/shaders/hudVertexShader.GLSL", "res/shaders/hudFragmentShader.GLSL");

	//create game objects
	MainMenu menu;

	//sdl stuff
	bool done = false;
	SDL_Event e;
	while(!done)
	{
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case (SDL_QUIT):
					done = true;
				break;

			}
		}
		//end event handling
		window.clear();

		hudShader.bind();
		menu.draw();


		//first we will draw the hud

		window.render();
	}

	return 0;
}