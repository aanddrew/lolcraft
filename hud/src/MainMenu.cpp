#include "../include/MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
:
picture("res/huds/Menu.png")
{
	//make sure our texture is loaded
	picture.load();

	//init our vertices
	//a little bit of hard coding never hurt anyone
	vertices = new float[3*6] 
	{
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,

		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
	};

	texCoords = new float[2*6]
	{
		1.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
	};

	//create our objects in the graphics card
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//==============Vertex Buffer=============
	glGenBuffers(1,&vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 6, 
							vertices, GL_STATIC_DRAW);

	// (ATTRIBUTE 0) will be the vertices position
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//========================================

	//==============TEXTURE COORD Buffer=============
	glGenBuffers(1,&texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 6, 
							texCoords, GL_STATIC_DRAW);

	// (ATTRIBUTE 1) will be the UV coords
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//========================================

	buttons = new Button[NUM_BUTTONS];

	//constructed our first button
	buttons[START].location.x = 630;
	buttons[START].location.y = 500;
	buttons[START].dimensions.x = 1330-630;
	buttons[START].dimensions.y = 610-500;
}

void MainMenu::draw(s3::Shader& shader)
{
	shader.bind();
	picture.bind();
	glBindVertexArray(0);
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

bool insideButton(const Button& button, int x, int y)
{
	return
	 (x > button.location.x &&
		x < button.location.x + button.dimensions.x &&
		y > button.location.y &&
		y < button.location.y + button.dimensions.y);
}

int MainMenu::click(int x, int y)
{
	//returns which button was clicked
	for(int i = 0; i < NUM_BUTTONS; i++)
	{
		if (insideButton(buttons[i], x, y))
			return i;
	}

	return -1;
}

bool MainMenu::isAlive(){return alive;}