#ifndef Collider_H
#define Collider_H

#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>

class Actor;
class World;

class Collider {
public:
	static bool isVectorContainingItem(const std::vector<sf::Vector2i>* vector, const sf::Vector2i* itemToSearch);
	static void getMapBlockOnPath(const int* numberOfStep, const World* world, sf::Vector2f startingPosition, float width, float heigh, sf::Vector2f path,
		std::vector<std::vector<sf::Vector2i>>* encounteredBlocks, const int* numberOfPointsPerBound);
	static sf::Vector2f calculateTravelableDistance(const Actor* actor, const World* world, const int* numberOfStep, sf::Vector2f path,
		std::vector<std::vector<sf::Vector2i>>* encounteredBlocks, bool* isTouchingVictoryBlock);
	static sf::Vector2f calculateTravelableDistance(const Actor* actor, const World* world, const int* numberOfStep, sf::Vector2f path,
		std::vector<std::vector<sf::Vector2i>>* encounteredBlocks);
	static bool isGoingOverAHole(const World* world, sf::Vector2f startPosition, sf::Vector2f direction);
};

#endif