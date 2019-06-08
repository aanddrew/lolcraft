#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <unordered_map>
#include "../../stage3/stage3.h"

class Block
{
public:
	Block(unsigned char ID);

	void draw(s3::Shader& shader);
private:
	void init();
	//a single byte for its ID
	unsigned char ID;

	enum meshID : unsigned char
	{
		CUBE_ALL,
		CUBE_FULL,

		NUM_MESH_IDS,
	};

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

	//our global table of textures and meshes 
	static std::vector<s3::Texture*> blockTextures;
	static std::vector<s3::Mesh*>	  blockMeshes;

	static std::unordered_map<unsigned char, unsigned char> whichMesh;
};

#endif
