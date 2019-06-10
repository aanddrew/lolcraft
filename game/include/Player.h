#ifndef PLAYER_H
#define PLAYER_H

#include "Block.h"

#include "../../stage3/stage3.h"
#include <glm/glm.hpp>

class Player
{
public:
	Player();

	void update(float dt);

	s3::Camera& getCamera();

	void setPos(glm::vec3);
	void setVelocity(glm::vec3);

	glm::vec3 getPos();
	glm::vec3 getVelocity();

	unsigned char getSelectedBlock();
	void setSelectedBlock(unsigned char block);
private:
	unsigned char selectedBlock;

	s3::Camera camera;
	float fov;

	glm::vec3 pos;
	glm::vec3 velocity;
};

#endif 