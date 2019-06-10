#include "stage3/stage3.h"
#include "hud/include/MainMenu.h"
#include "game/include/Block.h"
#include "game/include/Player.h"
#include "game/include/Level.h"
#include "hud/include/PlayerHud.h"

#include "utils/include/PlayerController.h"

#include <iostream>
#include <chrono>

#define WIDTH 1600
#define HEIGHT 900

void drawHud(Player& player);

int main()
{
	s3::Window window("lolcraft", WIDTH, HEIGHT);
	window.setBG(0.4, 0.6, 0.6);

	s3::Shader hudShader("res/shaders/hudVertexShader.GLSL", "res/shaders/hudFragmentShader.GLSL");
	// hudShader.createUniform("translate");
	// hudShader.setUniform("translate", glm::mat4(1.0f));

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
	Block::init();

	Player player;
	PlayerController pc(&player);
	PlayerHud ph(&player, (WIDTH*1.0f)/(HEIGHT*1.0f));

	Level level;

	//shader
	s3::Shader lightingShader("res/shaders/lightingVertexShader.GLSL", "res/shaders/lightingFragmentShader.GLSL");
	lightingShader.bind();
	lightingShader.createUniform("camera");
	lightingShader.setUniform("camera", player.getCamera().getMatrix());
	lightingShader.createUniform("model");

	//important that these are set after the creation of our blocks/level
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_CULL_FACE);

	bool inGame = true;

	//start recording dt
	float dt = 0.0005f * 10;
	std::chrono::high_resolution_clock clock;
	auto lastTime = clock.now();
	bool painting = false;

	while(open && inGame)
	{
		//getting the dt
		int ms = std::chrono::duration_cast<std::chrono::microseconds>(clock.now() - lastTime).count();
		lastTime = clock.now();
		//1,000,000 microseconds in a second
		dt = ((float)ms)/1000000; //this is in seconds
		//fps counter in terminal
		// std::cout << "fps: " << 1.0/dt << std::endl;

		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					open = false;
				break;
				case SDL_KEYDOWN:
				  pc.keyInput(e.key.keysym.sym, true);
				break;
				case SDL_KEYUP:
				  pc.keyInput(e.key.keysym.sym, false);
				break;

				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT:
							level.placeBlock(Block::texID::AIR, player.getPos(), player.getCamera().getForward(), true);
						break;
						case SDL_BUTTON_RIGHT:
							level.placeBlock(player.getSelectedBlock(), player.getPos(), player.getCamera().getForward(), false);
						break;
					}
					// painting = true;
				break;
				case SDL_MOUSEBUTTONUP:
					// painting = false;
				break;
			}
		}
		// if (painting)
		// 	level.placeBlock(player.getSelectedBlock(), player.getPos(), player.getCamera().getForward(), false);

		{//subscope for mouse input
			int x,y;
			SDL_GetMouseState(&x, &y);

			int dx = x - (WIDTH/2);
			int dy = y - (HEIGHT/2);

			pc.mouseInput(dx, dy);
			if (dx != 0 || dy != 0)
				SDL_WarpMouseInWindow(window.getSDLWindow(), WIDTH/2, HEIGHT/2);

			SDL_ShowCursor(0);
		}

		player.update(dt);
		pc.update(dt);

		//end event handling
		window.clear();

		lightingShader.bind();
		lightingShader.setUniform("camera", player.getCamera().getMatrix());
		level.draw(player.getPos(), lightingShader);

		ph.draw(hudShader);

		window.render();
	}

	Block::cleanUp();
	return 0;
}

void drawHud(Player& player)
{
	static bool init = false;

	if (!init)
	{
	}
}