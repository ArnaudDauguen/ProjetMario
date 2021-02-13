#pragma once

#include "../Enemy.h"

class EGoomba : public Enemy
{
public:
	EGoomba(Game* game, int x, int y, float scale, float mass, int textureIndex);
	~EGoomba() = default;
	void update(int deltaTime) override;
};

