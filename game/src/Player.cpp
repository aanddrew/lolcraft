#include "../include/Player.h"

Player::Player()
:
camera()
{
	fov = 70.0f;
	camera.setProjection(glm::perspective(fov, 16.0f/9.0f, 0.01f, 200.0f));

	setPos(glm::vec3(0.0f, 0.0f, 5.0f));
	setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));

	selectedBlock = Block::texID::LOG;
}

void Player::update(float dt)
{
	setPos(getPos() + getVelocity()*dt);
	//camera follows the player
	camera.setPos(getPos());
}

s3::Camera& Player::getCamera()
{
	return camera;
}

void Player::setPos(glm::vec3 posIn)
{
	pos = posIn;
}
void Player::setVelocity(glm::vec3 velIn)
{
	velocity = velIn;
}

glm::vec3 Player::getPos()
{
	return pos;
}

glm::vec3 Player::getVelocity()
{
	return velocity;
}

unsigned char Player::getSelectedBlock()
{
	return selectedBlock;
}
void Player::setSelectedBlock(unsigned char block)
{
	if (block > Block::NUM_TEX_IDS)
		selectedBlock = Block::texID::AIR;
	else
		selectedBlock = block;
}