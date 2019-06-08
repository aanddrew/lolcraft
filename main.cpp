#include "stage3/stage3.h"
#include "hud/include/MainMenu.h"
#include "game/include/Block.h"

#include <iostream>

int main()
{
	s3::Window window("lolcraft", 1600, 900);

	s3::Shader hudShader("res/shaders/hudVertexShader.GLSL", "res/shaders/hudFragmentShader.GLSL");

	bool open = true;

	//sdl stuff
	bool inMainMenu = true;
	SDL_Event e;

	{
	MainMenu menu;
	while(open && inMainMenu)
	{
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					open = false;
				break;
				case SDL_MOUSEBUTTONDOWN:
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					//don't know why but it's offset by like 100
					switch(menu.click(x+100,y+100))
					{
						case -1:
							//no button was hit
						break;
						case 0:
							inMainMenu = false;
						break;
					}
				}
				break;
			}
		}
		//end event handling
		window.clear();

		menu.draw(hudShader);


		//first we will draw the hud

		window.render();
	}
	}//our menu object dies here	

	//now that we are here we are in the game
	//create game objects
	s3::Shader lightingShader("res/shaders/lightingVertexShader.GLSL", "res/shaders/lightingFragmentShader.GLSL");

	s3::Camera cam;

	lightingShader.createUniform("camera");
	lightingShader.setUniform("camera", glm::perspective(70.0f, 16.0f/9.0f, 0.1f, 200.0f)*cam.getMatrix());

	lightingShader.createUniform("model");
	lightingShader.setUniform("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));


	Block b(0);

	bool inGame = true;

	while(open && inGame)
	{
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					open = false;
				break;
			}
		}
		//end event handling
		window.clear();

		//this is where the game will be renderedaa
		b.draw(lightingShader);

		window.render();
	}

	return 0;
}