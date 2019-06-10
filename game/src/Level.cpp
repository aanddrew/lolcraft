#include "../include/Level.h"

#include <iostream>
#include "../include/Block.h"

// s3::Mesh* Block::blockMesh = new s3::Mesh("game/res/blocks/mesh/cube_full.obj");
// Block* Level::blocks = nullptr;

Level::Level()
{
	blocks = new unsigned char[X_SIZE*Y_SIZE*Z_SIZE];

	for(int i = 0; i < X_SIZE*Y_SIZE*Z_SIZE; i++)
	{
		blocks[i] = Block::texID::AIR;
	}

	for(int x = 0; x < X_SIZE; x++)
	{
		for (int z = 0; z < Z_SIZE; z++)
		{
			for(int y = 0; y < 3; y++)
			{
				blocks[blockIndex(x, y, z)] = Block::texID::DIRT;
			}
			blocks[blockIndex(x, 3, z)] = Block::texID::GRASS;
		}
	}
	
	static bool init = false;
	if (!init)
	{
		//TODO: SPLIT THIS UP INTO CHUNKS - OS cannot find 134mb continuous memory
		init = true;
	}

	std::cout << "sizeof(Block): " << sizeof(Block) << std::endl;
	std::cout << "sizeof(unsigned char): " << sizeof(unsigned char) << std::endl;
}

Level::~Level()
{
	delete[] blocks;
}

Level::Level(const std::string& fileName)
{

}

void Level::placeBlock(unsigned char block, glm::vec3 pos, glm::vec3 forward, bool replace)
{
	// std::cout << "forward[0]: " << forward[0] << " [1]: " << forward[1] << " [2]: " << forward[2] << std::endl;
	int x = (int)pos[0];
	int y = (int)pos[1];
	int z = (int)pos[2];

	float dxdy = forward[0]/forward[1];
	float dxdz = forward[0]/forward[2];
	float dydx = forward[1]/forward[0];
	float dydz = forward[1]/forward[2];
	float dzdx = forward[2]/forward[0];
	float dzdy = forward[2]/forward[1];

	glm::vec3 marcher = pos;
	float mod = 1.0;
	int last_step = -1;
	for(int i = 0; i < 100; i++)
	{
		int mx = (int)marcher[0];
		int my = (int)marcher[1];
		int mz = (int)marcher[2];

		float tX = marcher[0] - (mx*1.0f);
		float tY = marcher[1] - (my*1.0f);
		float tZ = marcher[2] - (mz*1.0f);

		// std::cout << "tx: " << tX << " ty: " << tY << " tZ: " << tZ << std::endl;

		if (blockAt(mx, my, mz) != Block::texID::AIR)
		{
			if (!replace)
			{
				int dMx = 0;
				int dMy = 0;
				int dMz = 0;

				float threshold = 0.05;

				if (abs(tX) < threshold || abs(tX) > (1.0f - threshold))
					dMx = (forward[0] > 0 ? -1 : 1);
				if (abs(tY) < threshold || abs(tY) > (1.0f - threshold))
					dMy = (forward[1] > 0 ? -1 : 1);
				if (abs(tZ) < threshold || abs(tZ) > (1.0f - threshold))
					dMz = (forward[2] > 0 ? -1 : 1);

				//lets do some error analysis if we didn't find anything in threshold
				if (!dMx && !dMy && !dMz)
				{
					if (tX > 0.5)
						tX -= 1.0f;
					if (tY > 0.5)
						tY -= 1.0f;
					if (tZ > 0.5)
						tZ -= 1.0f;

					tX = abs(tX);
					tY = abs(tY);
					tZ = abs(tZ);

					if (tX < tY && tX < tZ)
						dMx = (forward[0] > 0 ? -1 : 1);
					else if (tZ < tX && tZ < tY)
						dMz = (forward[2] > 0 ? -1 : 1);
					else
						dMy = (forward[1] > 0 ? -1 : 1);
				}

				if (validIndex(mx + dMx, my + dMy, mz + dMz))
					blocks[blockIndex(mx + dMx, my + dMy, mz + dMz)] = block;
					break;
			}
			else
			{
				blocks[blockIndex(mx, my, mz)] = block;
			}
			break;
		}

		float dx = marcher[0] - (int)(marcher[0]);
		float dy = marcher[1] - (int)(marcher[1]);
		float dz = marcher[2] - (int)(marcher[2]);

		if (forward[0] < 0)
		{
			last_step = 0;
			dx = 1.0f - abs(dx);
		}
		if (forward[1] < 0)
		{
			last_step = 1;
			dy = 1.0f - abs(dy);
		}
		if (forward[2] < 0)
		{
			last_step = 2;
			dz = 1.0f - abs(dz);
		}

		//dx is smallest
		if (dx < dy && dx < dz)
		{
			marcher += forward*dx*mod;
		}
		//dy is smallest
		else if (dy < dx && dy < dz)
		{
			marcher += forward*dy*mod;
		}
		//dz is smallest
		else
		{
			marcher += forward*dz*mod;
		}
	}

	// blocks[blockIndex(x,y,z)] = block;
}

unsigned char Level::blockAt(int x, int y, int z) const
{
	if (x < 0 || y < 0 || z < 0 || x >= X_SIZE || y >= Y_SIZE || z >= Z_SIZE)
	{
		//the rest of the world is assumed to be made out of air
		return Block::texID::AIR;
	}
	return blocks[blockIndex(x, y, z)];
}

int Level::blockIndex(int x, int y, int z)
{
	return x + y*(X_SIZE*Z_SIZE) + z*(X_SIZE);
}

bool Level::validIndex(int x, int y, int z)
{
	if (x < 0 || y < 0 || z < 0 || x >= X_SIZE || y >= Y_SIZE || z >= Z_SIZE)
	{
		return false;
	}
	return true;
}

bool Level::blockVisible(int x, int y, int z, glm::vec3 pos)
{
	int xDir = (pos[0] > x ? 1 : -1);
	int yDir = (pos[1] > y ? 1 : -1);
	int zDir = (pos[2] > z ? 1 : -1);

	if
	(
		blockAt(x + 0   , y + 0   , z + zDir) == Block::texID::AIR ||
		blockAt(x + 0   , y + yDir, z + 0   ) == Block::texID::AIR ||
		blockAt(x + 0   , y + yDir, z + zDir) == Block::texID::AIR ||
		blockAt(x + xDir, y + 0   , z + 0   ) == Block::texID::AIR ||
		blockAt(x + xDir, y + 0   , z + zDir) == Block::texID::AIR ||
		blockAt(x + xDir, y + yDir, z + 0   ) == Block::texID::AIR ||
		blockAt(x + xDir, y + yDir, z + zDir) == Block::texID::AIR
	)
		return true;

	return false;
}

//the position is used for occlusion culling
void Level::draw(glm::vec3 pos, s3::Shader& shader)
{
	shader.bind();
	for(int x = 0; x < X_SIZE; x++)
	{
		for (int z = 0; z < Z_SIZE; z++)
		{
			for(int y = 0; y < Y_SIZE; y++)
			{
				if (blockAt(x,y,z) == Block::texID::AIR)
					continue;
				if (blockVisible(x, y, z, pos))
				{
					shader.setUniform("model", glm::translate(glm::mat4(1.0f), glm::vec3(x*1.0f, y*1.0f, z*1.0f)));
					Block::draw(blocks[blockIndex(x, y, z)], shader);
				}
			}
		}
	}
}