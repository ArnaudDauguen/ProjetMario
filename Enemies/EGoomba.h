#pragma once

#include "../Enemy.h"

class EGoomba : public Enemy
{
public:
	EGoomba(Game* game, int x, int y, float scale, float mass, int textureIndex, sf::Vector2f speed);
	~EGoomba() = default;
	
	void calculateDeathCollisionBox() override;

protected:
	void move(sf::Vector2f path) override;
};

