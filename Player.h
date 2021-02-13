#pragma once

#include "Actor.h"

namespace sf {
	class RenderWindow;
}

class Game;

class Player : public Actor
{
public:
	Player(Game* game, int x, int y, float scale, float mass, sf::Vector2f speed);

	void handleInputs(int deltaTime);
	
protected:
	void move(sf::Vector2f path) override;
	void applyGravity(int deltaTime) override;

private:
	
};

