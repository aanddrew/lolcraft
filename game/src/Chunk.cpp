#include "../include/Chunk.h"

Chunk::Chunk()
{
	blocks = new unsigned char[X_SIZE*Y_SIZE*Z_SIZE*64*64];
	// blocks.reserve(X_SIZE*Y_SIZE*Z_SIZE);
	// blocks = new Block[16*128];
}

Chunk::~Chunk()
{
	delete[] blocks;
}