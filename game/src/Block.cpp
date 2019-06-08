#include "../include/Block.h"

//init static members
//these must be vectors of pointers because c++ does not like 
//overwriting the objects after their default constructors have been called
//I think it has to do with the shitty default cube code in the mesh class
std::vector<s3::Texture*> Block::blockTextures = std::vector<s3::Texture*>();
std::vector<s3::Mesh*>	  Block::blockMeshes = std::vector<s3::Mesh*>();

int Block::NUM_TEX_IDS = AIR;

//now thats a long line of code
std::unordered_map<unsigned char, unsigned char> Block::whichMesh = std::unordered_map<unsigned char, unsigned char>();

Block::Block(unsigned char ID)
{
	this->ID = ID;

	static bool initialized = false;
	if (!initialized)
	{
		init();
	}
}

void Block::init()
{
	blockTextures.reserve(NUM_TEX_IDS);
	blockMeshes.reserve(NUM_MESH_IDS);

	//creating textures
	blockTextures[DIRT] = new s3::Texture("game/res/blocks/tex/dirt.png");
	blockTextures[GRASS] = new s3::Texture("game/res/blocks/tex/grass.png");
	blockTextures[STONE] = new s3::Texture("game/res/blocks/tex/stone.png");
	blockTextures[COBBLE] = new s3::Texture("game/res/blocks/tex/stone.png");
	blockTextures[LOG] = new s3::Texture("game/res/blocks/tex/log.png");
	blockTextures[LEAF] = new s3::Texture("game/res/blocks/tex/leaf.png");
	blockTextures[PLANK] = new s3::Texture("game/res/blocks/tex/plank.png");

	//loading them
	for(int i = 0; i < NUM_TEX_IDS; i++)
	{
		blockTextures[i]->load();
	}

	//creating meshes
	blockMeshes[CUBE_ALL] = new s3::Mesh("game/res/blocks/mesh/cube_all.obj");
	blockMeshes[CUBE_FULL] = new s3::Mesh("game/res/blocks/mesh/cube_full.obj");

	//loading them
	for(int i = 0; i < NUM_MESH_IDS; i++)
	{
		blockMeshes[i]->load();
	}
}

void Block::draw(s3::Shader& shader)
{
	shader.bind();
	blockTextures[ID]->bind();
	blockMeshes[whichMesh[ID]]->bind();

	blockMeshes[whichMesh[ID]]->draw();
}