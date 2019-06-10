#ifndef CHUNK_H
#define CHUNK_H

#include "Block.h"
#include "../../stage3/stage3.h"

class Chunk
{
public:
	Chunk();
	~Chunk();
	Chunk(unsigned char * start);

	void draw(s3::Shader& shader);

	static const int X_SIZE = 16;
	static const int Y_SIZE = 128;
	static const int Z_SIZE = 16;
private:
	// Block blocks[16*128*16];
	unsigned char* blocks;
	// std::vector<Block> blocks;
};

#endif