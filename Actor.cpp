#include "Actor.h"

#include "Collider.h"
#include "World.h"


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
    const int numberOfStep = (int)ceil(float(sqrt(path.x * path.x + path.y * path.y)) / this->m_game->m_world->getBlockSize()) * 2;
    Collider::getMapBlockOnPath(&numberOfStep, this->m_game->m_world, this->m_sprite.getPosition(), this->GetCharacterSize().x, this->GetCharacterSize().y, path,
        &blockOnPath, &numberOfPointsPerBound);

    // Calculate travelable distance
    return Collider::calculateTravelableDistance(this, this->m_game->m_world, &numberOfStep, path,
        &blockOnPath);
}

// Must be overrided for world translation
void Actor::move(sf::Vector2f path)
{
    // CALCULATE MOVEMENT
    sf::Vector2f travelableDistance = this->calculateMovementVector(path);

    // MOVE
    this->m_sprite.move(travelableDistance);
}