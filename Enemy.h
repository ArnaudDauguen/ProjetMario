#pragma once

#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy() = default;
	virtual ~Enemy() = default;


	float GetLocationX()
	{
		return this->m_sprite.getPosition().x;
	}
protected:

};