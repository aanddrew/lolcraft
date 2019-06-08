#include "../include/MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
:
picture("res/huds/Menu.png")
{
	picture.load();
	//init our vertices
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

	// for(int i = 0; i < 6; i++)
	// {
	// 	std::cout << vertices[i*3 + 0] << ", " << vertices[i*3 + 1] << ", " << vertices[i*3 + 2] << std::endl;
	// }

	// for(int i = 0; i < 6; i++)
	// {
	// 	std::cout << texCoords[i*2 + 0] << ", " << texCoords[i*2 + 1] << std::endl;
	// }

	std::cout << vertices << std::endl;
	std::cout << texCoords << std::endl;

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

}

void MainMenu::draw()
{
	picture.bind();
	glBindVertexArray(0);
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

bool MainMenu::isAlive(){return alive;}