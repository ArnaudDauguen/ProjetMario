#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


#include "Actor.h"
#include "IDrawableObject.h"
#include "IUpdatableObject.h"

namespace sf {
	class RenderWindow;
}

class Game;

class Player : public Actor
{
public:
	Player(Game* game, int x, int y, float scale, float mass);

	void handleInputs(int deltaTime);
	
protected:
	void move(sf::Vector2f path) override;

private:
	
};

