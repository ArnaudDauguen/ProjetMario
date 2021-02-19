#pragma once

#include "../Enemy.h"

class EThwomp : public Enemy
{
public:
	EThwomp(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale, float mass, float playerDetectionXRange, float timeOnGround, float ascendSpeed);
	EThwomp(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale) : EThwomp(game, startingPosition, textureIndex, scale, 2.f, 1.75f, 1500.f, 1.25f) {};
	EThwomp(Game* game, sf::Vector2f startingPosition, int textureIndex) : EThwomp(game, startingPosition, textureIndex, { 3.75f, 5.75f }) {};
	EThwomp(Game* game, sf::Vector2f startingPosition) : EThwomp(game, startingPosition, 46) {};
	~EThwomp() = default;

	void update(int deltaTime) override;
	
	void calculateDeathCollisionBox() override;
	bool isColliderInKillZone(sf::FloatRect* globalBoundToTest) override { return false; };

protected:
	sf::Vector2f startPosition;
	
	bool m_waitingForPlayer = true;
	bool m_isFalling = false;
	float playerDetectionXRange = 2.f;  // block
	float timeOnGround = 2000.f;		// millisecond
	float ascendSpeed = 1.f;			// block/sec
	float timer = 0.f;
	sf::FloatRect m_agroArea;

	sf::Vector2f move(sf::Vector2f path) override;
	bool isPlayerInRange();
	void buildAgroArea();
};

