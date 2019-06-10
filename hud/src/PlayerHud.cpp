#include "../include/PlayerHud.h"

PlayerHud::PlayerHud(Player* player, float ar)
:
crossHair("res/huds/crossHair.png"),
itemBar("res/huds/itemBar.png")
{
	crossHair.load();
	itemBar.load();

	float halfBarWidth = (820*1.0f)/(1600*1.0f)/2.0f;
	float barHeight = (100*1.0f)/(900*1.0f);

	float chWidth = 0.01f;
	float chHeight = 0.01f*ar; 

	barVertices = new float[3*6] 
	{
		0.0f + halfBarWidth, -1.0f + barHeight, 0.0f,
		0.0f - halfBarWidth, -1.0f + barHeight, 0.0f,
		0.0f + halfBarWidth, -1.0f, 0.0f,

		0.0f - halfBarWidth, -1.0f, 0.0f,
		0.0f + halfBarWidth, -1.0f, 0.0f,
		0.0f - halfBarWidth, -1.0f + barHeight, 0.0f,
	};

	chVertices = new float[3*6]
	{
		0.0f + chWidth, 0.0f + chHeight, 0.0f,
		0.0f - chWidth, 0.0f + chHeight, 0.0f,
		0.0f + chWidth, 0.0f - chHeight, 0.0f,

		0.0f - chWidth, 0.0f - chHeight, 0.0f,
		0.0f + chWidth, 0.0f - chHeight, 0.0f,
		0.0f - chWidth, 0.0f + chHeight, 0.0f,
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

	//LOADING ITEM BAR ===============================================
	//create our objects in the graphics card
	glGenVertexArrays(1, &barVAO);
	glBindVertexArray(barVAO);

	//==============Vertex Buffer=============
	glGenBuffers(1,&barVertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, barVertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 6, 
							barVertices, GL_STATIC_DRAW);

	// (ATTRIBUTE 0) will be the vertices position
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, barVertexVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//========================================

	//==============TEXTURE COORD Buffer=============
	glGenBuffers(1,&barTexCoordObject);
	glBindBuffer(GL_ARRAY_BUFFER, barTexCoordObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 6, 
							texCoords, GL_STATIC_DRAW);

	// (ATTRIBUTE 1) will be the UV coords
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, barTexCoordObject);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//========================================


	//LOADING CROSSHAIR ==============================================
	glGenVertexArrays(1, &chVAO);
	glBindVertexArray(chVAO);

	//==============Vertex Buffer=============
	glGenBuffers(1,&chVertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, chVertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 6, 
							chVertices, GL_STATIC_DRAW);

	// (ATTRIBUTE 0) will be the vertices position
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, chVertexVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//========================================

	//==============TEXTURE COORD Buffer=============
	glGenBuffers(1,&chTexCoordObject);
	glBindBuffer(GL_ARRAY_BUFFER, chTexCoordObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 6, 
							texCoords, GL_STATIC_DRAW);

	// (ATTRIBUTE 1) will be the UV coords
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, chTexCoordObject);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//========================================
}

void PlayerHud::draw(s3::Shader& shader)
{
	glClear(GL_DEPTH_BUFFER_BIT);

	shader.bind();
	crossHair.bind();
	glBindVertexArray(0);
	glBindVertexArray(chVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	itemBar.bind();
	glBindVertexArray(0);
	glBindVertexArray(barVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

PlayerHud::~PlayerHud()
{
	delete[] barVertices;
	delete[] chVertices;
	delete[] texCoords;
}