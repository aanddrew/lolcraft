#ifndef LEVEL_H
#define LEVEL_H

#include "Block.h"
#include "Chunk.h"
#include "../../stage3/stage3.h"

class Level
{
public:
	Level();
	~Level();
	Level(const std::string& fileName);
	void draw(glm::vec3 pos,s3::Shader& shader);

	void placeBlock(unsigned char block, glm::vec3 pos, glm::vec3 forward, bool replace);

	unsigned char blockAt(int x, int y, int z) const;

	// static const int NUM_CHUNKS_X = 64;
	// static const int NUM_CHUNKS_Y = 64;
	static const int X_SIZE = 64;
	static const int Y_SIZE = 16;
	static const int Z_SIZE = 64;
private:
	bool blockVisible(int x, int y , int z, glm::vec3 pos);
	static bool validIndex(int x, int y, int z);
	static int blockIndex(int x, int y, int z);

	unsigned char* blocks;
};

#endif