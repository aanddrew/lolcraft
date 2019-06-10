#include "../include/Block.h"

#include <iostream>

//init static members
//these must be vectors of pointers because c++ does not like 
//overwriting the objects after their default constructors have been called
//I think it has to do with the shitty default cube code in the mesh class
std::vector<s3::Texture*> Block::blockTextures = std::vector<s3::Texture*>();
//we only have 1 mesh
s3::Mesh* Block::blockMesh = new s3::Mesh("game/res/blocks/mesh/cube_full.obj");

int Block::NUM_TEX_IDS = AIR;


// Block::Block()
// {
// 	this->ID = AIR;

// 	static bool initialized = false;
// 	if (!initialized)
// 	{
// 		init();
// 	}
// }

// Block::Block(unsigned char ID)
// {
// 	this->ID = ID;

// 	static bool initialized = false;
// 	if (!initialized)
// 	{
// 		init();
// 	}
// }

void Block::init()
{
	blockTextures.reserve(NUM_TEX_IDS);
	//creating textures
	blockTextures[DIRT] = new s3::Texture("game/res/blocks/tex/dirt.png");
	blockTextures[GRASS] = new s3::Texture("game/res/blocks/tex/grass.png");
	blockTextures[STONE] = new s3::Texture("game/res/blocks/tex/stone.png");
	blockTextures[COBBLE] = new s3::Texture("game/res/blocks/tex/cobble.png");
	blockTextures[LOG] = new s3::Texture("game/res/blocks/tex/log.png");
	blockTextures[LEAF] = new s3::Texture("game/res/blocks/tex/leaf.png");
	blockTextures[PLANK] = new s3::Texture("game/res/blocks/tex/plank.png");

	//loading them
	for(int i = 0; i < NUM_TEX_IDS; i++)
	{
		blockTextures[i]->load();
	}

	//load mesh
	blockMesh->load();
}

void Block::cleanUp()
{
	for(int i = 0; i < NUM_TEX_IDS; i++)
	{
		if (blockTextures[i] != nullptr)
			delete blockTextures[i];
	}

	if (blockMesh != nullptr)
		delete blockMesh;
}

void Block::draw(unsigned char ID, s3::Shader& shader)
{
	if (ID == AIR)
		return;
	shader.bind();
	blockTextures[ID]->bind();

	blockMesh->bind();
	blockMesh->draw();
}
