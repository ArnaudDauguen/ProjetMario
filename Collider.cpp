#include "Collider.h"
#include <utility>
#include <vector>

#include "World.h"

bool Collider::isVectorContainingItem(const std::vector<sf::Vector2i>* vector, const sf::Vector2i* itemToSearch)
{
    for (sf::Vector2i obj : *vector)
    {
        if (itemToSearch->x == obj.x && itemToSearch->y == obj.y) return true;
    }

    return false;
}

void Collider::getMapBlockOnPath(const int* numberOfStep, World* world, sf::Vector2f startingPosition, float width, float heigh, sf::Vector2f path, 
	std::vector<sf::Vector2i>* firstCornerEncounteredBlocks,
	std::vector<sf::Vector2i>* secondCornerEncounteredBlocks,
	std::vector<sf::Vector2i>* thirdCornerEncounteredBlocks,
	std::vector<sf::Vector2i>* fourthCornerEncounteredBlocks)
{
    sf::Vector2f travelledDistance = { 0, 0 };
    const sf::Vector2f oneStepTravelDistance = { path.x / *numberOfStep, path.y / *numberOfStep };

    sf::Vector2f firstCorner = startingPosition;                                   //top left
    sf::Vector2f secondCorner = {firstCorner.x + width, firstCorner.y};          //top right
    sf::Vector2f thirdCorner = {firstCorner.x + width, firstCorner.y + heigh}; //bottom right
    sf::Vector2f fourthCorner = {firstCorner.x, firstCorner.y + heigh};          //bottom left

    sf::Vector2i tmpBlock;
    for(int step = 0; step < *numberOfStep; step++)
    {
        firstCorner += oneStepTravelDistance;
        secondCorner += oneStepTravelDistance;
        thirdCorner += oneStepTravelDistance;
        fourthCorner += oneStepTravelDistance;

        firstCornerEncounteredBlocks->push_back(world->PositionOnScreenToMapBlockIndex(firstCorner));
        secondCornerEncounteredBlocks->push_back(world->PositionOnScreenToMapBlockIndex(secondCorner));
        thirdCornerEncounteredBlocks->push_back(world->PositionOnScreenToMapBlockIndex(thirdCorner));
        fourthCornerEncounteredBlocks->push_back(world->PositionOnScreenToMapBlockIndex(fourthCorner));
    	
        travelledDistance += oneStepTravelDistance;
    }
}
