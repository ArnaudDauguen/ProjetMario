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

class Player : public Actor, public IDrawableObject, public IUpdatableObject
{
public:
	Player(Game* game, int x, int y, float scale);

	void handleInputs(int deltaTime);
	
	void update(int deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	bool mustDie() override { return false; }
protected:
	void move(sf::Vector2f path) override;

private:
	
};

