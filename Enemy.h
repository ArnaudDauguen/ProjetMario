#pragma once

#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy() = default;
	virtual ~Enemy() = default;

	virtual void update(int deltaTime) override;
protected:

};