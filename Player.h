#pragma once

#include <SFML/Window/Keyboard.hpp>

#include "Actor.h"

namespace sf {
	class RenderWindow;
}

class Game;

class Player : public Actor
{
public:
	Player(Game* game, sf::Vector2f startingPosition, float scale, float mass, sf::Vector2f speed);

	void handleInputs(int deltaTime, sf::Event* event);
	
protected:
	float m_jumpStrength = 3.f;
	bool m_isOnGround = false;
	bool m_hasAlreadyJumped = false;
	
	void move(sf::Vector2f path) override;
	void applyGravity(int deltaTime) override;
	void jump();

private:
	sf:: Keyboard::Key m_jumpKey = sf::Keyboard::Up;
};

