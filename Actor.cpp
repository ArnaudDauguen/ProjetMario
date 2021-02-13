#include "Actor.h"

#include <iostream>


#include "Collider.h"
#include "World.h"
#include "Game.h"

void Actor::applyGravity(int deltaTime) // This module is completely separate from the rest of movement methods
{
    if (this->m_mass == 0)
        return;
	
    sf::Vector2f travelableDistance = this->calculateMovementVector({ 0.f, this->m_mass * this->m_game->gravityStrength * deltaTime });
    if (travelableDistance == sf::Vector2f(0.f, 0.f))
        return;
	
    this->m_sprite.move(travelableDistance);
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

void Actor::move(sf::Vector2f path)
{
    // CALCULATE MOVEMENT
    sf::Vector2f travelableDistance = this->calculateMovementVector(path);
    if (travelableDistance == sf::Vector2f(0.f, 0.f))
        return;
    
    // MOVE
    this->m_sprite.move(travelableDistance);
}

void Actor::forceMove(sf::Vector2f distance)
{
    this->m_sprite.move(distance);
}