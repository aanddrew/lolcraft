#ifndef MAINMENU_H
#define MAINMENU_H

#include <GL/glew.h>
#include "../../stage3/stage3.h"

class MainMenu
{
public:
	MainMenu();

	void draw();

	bool isAlive();
private:
	s3::Texture picture;

	//opengl voodo
	float* vertices;
	float* texCoords;

	GLuint vertexArrayObject;
	GLuint vertexBuffer;
	GLuint texCoordBuffer;

	bool alive;
};

#endif