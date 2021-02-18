#pragma once

#include "../Enemy.h"

class EGoomba : public Enemy
{
public:
	EGoomba(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale, float mass, sf::Vector2f speed);
	EGoomba(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale) : EGoomba(game, startingPosition, textureIndex, scale, 0.5f, { 0.075f, 0.f }) {};
	EGoomba(Game* game, sf::Vector2f startingPosition, int textureIndex) : EGoomba(game, startingPosition, textureIndex, { 1.75f, 1.75f }) {};
	EGoomba(Game* game, sf::Vector2f startingPosition) : EGoomba(game, startingPosition, 70) {};
	~EGoomba() = default;
	
	void calculateDeathCollisionBox() override;

protected:
	sf::Vector2f move(sf::Vector2f path) override;
};

