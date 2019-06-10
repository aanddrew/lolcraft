#ifndef PLAYERHUD_H
#define PLAYERHUD_H

#include "../../stage3/stage3.h"
#include "../../game/include/Player.h"

#include <GL/glew.h>

class PlayerHud
{
public:
	PlayerHud(Player* playerIn, float ar);
	~PlayerHud();

	void draw(s3::Shader& shader);
private:
	s3::Texture crossHair;
	s3::Texture itemBar;

	//opengl voodoo
	float* barVertices;
	float* chVertices;
	//this is the same for both
	float* texCoords;

	GLuint barVAO;
	GLuint barVertexVBO;
	GLuint barTexCoordObject;

	GLuint chVAO;
	GLuint chVertexVBO;
	GLuint chTexCoordObject;
};

#endif