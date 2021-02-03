#ifndef Collider_H
#define Collider_H

#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>

class World;

class Collider {
public:
	static bool isVectorContainingItem(const std::vector<sf::Vector2i>* vector, const sf::Vector2i* itemToSearch);
	static void getMapBlockOnPath(const int* numberOfStep, World* world, sf::Vector2f startingPosition, float width, float heigh, sf::Vector2f path,
		std::vector<sf::Vector2i>* firstCornerEncounteredBlocks,
		std::vector<sf::Vector2i>* secondCornerEncounteredBlocks,
		std::vector<sf::Vector2i>* thirdCornerEncounteredBlocks,
		std::vector<sf::Vector2i>* fourthCornerEncounteredBlocks);
};

#endif