#include "Collider.h"

#include <iostream>
#include <utility>
#include <vector>

#include "World.h"
#include "Actor.h"

bool Collider::isVectorContainingItem(const std::vector<sf::Vector2i>* vector, const sf::Vector2i* itemToSearch)
{
    for (sf::Vector2i obj : *vector)
    {
        if (itemToSearch->x == obj.x && itemToSearch->y == obj.y) return true;
    }

    return false;
}

void Collider::getMapBlockOnPath(const int* numberOfStep, const World* world, sf::Vector2f startingPosition, float width, float heigh, sf::Vector2f path, 
	std::vector<std::vector<sf::Vector2i>>* encounteredBlocks, const int* numberOfPointsPerBound)
{
    sf::Vector2f travelledDistance = { 0, 0 };
    const sf::Vector2f oneStepTravelDistance = { path.x / *numberOfStep, path.y / *numberOfStep };
    std::vector<sf::Vector2f> pointsToCheck;

	for(float i = 0.f; i < *numberOfPointsPerBound; ++i)
	{
        float boundAdvancement = i / float(*numberOfPointsPerBound);
        pointsToCheck.push_back({ startingPosition.x + (width * boundAdvancement), startingPosition.y });                   //top left TO top right
        pointsToCheck.push_back({ startingPosition.x + width, startingPosition.y + (heigh * boundAdvancement)});          //top right TO bottom right
        pointsToCheck.push_back({ startingPosition.x + width - (width * boundAdvancement), startingPosition.y + heigh }); //bottom right TO bottom left
        pointsToCheck.push_back({ startingPosition.x, startingPosition.y + heigh - (heigh * boundAdvancement)});            //bottom left TO top left
	}
    
    for(int step = 0; step < *numberOfStep; step++)
    {
    	// for each points to check
    	for(int i = 0; i < pointsToCheck.size(); ++i)
    	{
            pointsToCheck[i] += oneStepTravelDistance;
            encounteredBlocks->at(i).push_back(world->PositionOnScreenToMapBlockIndex(pointsToCheck[i]));
    	}
    	
        travelledDistance += oneStepTravelDistance;
    }
}

sf::Vector2f Collider::calculateTravelableDistance(const Actor* actor, const World* world, const int* numberOfStep, sf::Vector2f path,
    std::vector<std::vector<sf::Vector2i>>* blockOnPath)
{

    sf::Vector2f travelableDistance = { 0, 0 };
    const sf::Vector2f stepDistance = { path.x / *numberOfStep, path.y / *numberOfStep };
    for (int step = 0; step < *numberOfStep; ++step)
    {
        bool isValid = true;

    	// Check all points
    	for(auto vector : *blockOnPath)
    	{
			// Check if target block is in map
            isValid = isValid && vector.at(step).x >= 0
                && vector.at(step).x < world->GetSize().x
                && vector.at(step).y >= 0
                && vector.at(step).y < world->GetSize().y
                // Check if target block is valid destination
                && world->GetBlocks()[vector.at(step).x][vector.at(step).y] == -1; //TODO update to allow use of array of valid blockIds
    	}
    	
    	if(isValid) travelableDistance += stepDistance;
        else break;
    }

    return travelableDistance;
}
