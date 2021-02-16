#pragma once

#include "../Enemy.h"

class EGoomba : public Enemy
{
public:
	EGoomba(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale, float mass, sf::Vector2f speed);
	EGoomba(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale);
	EGoomba(Game* game, sf::Vector2f startingPosition, int textureIndex);
	~EGoomba() = default;
	
	void calculateDeathCollisionBox() override;

protected:
	sf::Vector2f move(sf::Vector2f path) override;
};

