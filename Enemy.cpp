#include "Enemy.h"


void Enemy::update(int deltaTime)
{
	if (this->mustDie())
		return;

	this->applyGravity(deltaTime);
	this->move({ this->m_speed.x * deltaTime, this->m_speed.y * deltaTime });
}