#ifndef MAINMENU_H
#define MAINMENU_H

#include <GL/glew.h>
#include "../../stage3/stage3.h"

struct vec2
{
	int x;
	int y;
};

struct Button
{
	vec2 location;
	vec2 dimensions;
};

class MainMenu
{
public:
	MainMenu();

	void draw(s3::Shader& shader);

	int click(int x, int y);

	bool isAlive();
private:
	s3::Texture picture;

	//opengl voodoo
	float* vertices;
	float* texCoords;

	GLuint vertexArrayObject;
	GLuint vertexBuffer;
	GLuint texCoordBuffer;
	//end voodoo

	Button* buttons;

	enum buttonNames
	{
		START,

		NUM_BUTTONS,
	};

	bool alive;
};

#endif