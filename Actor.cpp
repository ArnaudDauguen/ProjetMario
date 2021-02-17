#include "Actor.h"

#include <iostream>


#include "Collider.h"
#include "World.h"
#include "Game.h"

void Actor::draw(sf::RenderWindow& window)
{
	if(this->m_game->m_screen.intersects(this->m_sprite.getGlobalBounds()))
		window.draw(this->m_sprite);
}


sf::Vector2f Actor::applyGravity(int deltaTime) // This module is completely separate from the rest of movement methods
{
    if (this->m_mass == 0)
        return {0, 0};
	
    sf::Vector2f travelableDistance = this->calculateMovementVector({ 0.f, this->m_mass * this->m_game->m_gravityStrength * deltaTime });
    if (travelableDistance == sf::Vector2f(0.f, 0.f))
        return {0, 0};
	
    this->m_sprite.move(travelableDistance);
    return travelableDistance;
}


sf::Vector2f Actor::calculateMovementVector(sf::Vector2f path)
{
    // CALCULATE MOVEMENT
    // Get collision data
    const int numberOfPointsPerBound = 1 + (int)floor(std::max(this->GetCharacterSize().x / this->m_game->m_world->getBlockSize(), this->GetCharacterSize().y / this->m_game->m_world->getBlockSize()));
    std::vector<std::vector<sf::Vector2i>> blockOnPath;
	for(int i = 0; i < 4 * numberOfPointsPerBound; i++)
	{
        blockOnPath.push_back({});
	}
    const int numberOfStep = (int)ceil(float(sqrt(path.x * path.x + path.y * path.y)) / this->m_game->m_world->getBlockSize()) * 4;
    Collider::getMapBlockOnPath(&numberOfStep, this->m_game->m_world, this->m_sprite.getPosition(), this->GetCharacterSize().x, this->GetCharacterSize().y, path,
        &blockOnPath, &numberOfPointsPerBound);

    // Calculate travelable distance
    return Collider::calculateTravelableDistance(this, this->m_game->m_world, &numberOfStep, path,
        &blockOnPath);
}

sf::Vector2f Actor::move(sf::Vector2f path)
{
    // CALCULATE MOVEMENT
    sf::Vector2f travelableDistance = this->calculateMovementVector(path);
    if (travelableDistance == sf::Vector2f(0.f, 0.f))
        return travelableDistance;
    
    // MOVE
    this->m_sprite.move(travelableDistance);
    return travelableDistance;
}

void Actor::forceMove(sf::Vector2f distance)
{
    this->m_sprite.move(distance);
}

void Actor::calculateDeathCollisionBox()
{
    this->deathCollisionBox = this->m_sprite.getGlobalBounds();
}

bool Actor::isColliding(sf::FloatRect* globalBoundToTest)
{
    return this->m_sprite.getGlobalBounds().intersects(*globalBoundToTest);
}

bool Actor::isColliderInKillZone(sf::FloatRect* globalBoundToTest)
{
    this->calculateDeathCollisionBox();
    return this->deathCollisionBox.intersects(*globalBoundToTest);
}

bool Actor::isGoingOverAHole(sf::Vector2f direction)
{
    const sf::Vector2f startPosition = {
        this->m_sprite.getPosition().x + ((direction.x < 0.f) ? 0 : this->m_sprite.getTexture()->getSize().x * this->m_sprite.getScale().x),
        this->m_sprite.getPosition().y + this->m_sprite.getTexture()->getSize().y * this->m_sprite.getScale().y
    };
	return Collider::isGoingOverAHole(this->m_game->m_world, startPosition, direction);
}


