#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <unordered_map>
#include "../../stage3/stage3.h"

class Block
{
public:
	// Block();
	// Block(unsigned char ID);

	static void draw(unsigned char, s3::Shader& shader);

	enum texID : unsigned char
	{
		DIRT,
		GRASS,
		STONE,
		COBBLE,
		LOG,
		LEAF,
		PLANK,

		AIR,
	};

	static int NUM_TEX_IDS;

	static void init();

	static void cleanUp();

private:
	//a single byte for its ID
	// unsigned char ID;

	//our global table of textures and meshes 
	static std::vector<s3::Texture*> blockTextures;
	static s3::Mesh* blockMesh;
};

#endif
