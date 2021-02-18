#pragma once

#include <SFML/Window/Keyboard.hpp>

#include "../Actor.h"

namespace sf {
	class RenderWindow;
}

class Game;

class Player : public Actor
{
public:
	Player(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale, float mass, sf::Vector2f speed);
	Player(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale) : Player(game, startingPosition, textureIndex, scale, 1.1f, {0.4f, 0.f}) {};
	Player(Game* game, sf::Vector2f startingPosition, int textureIndex) : Player(game, startingPosition, textureIndex, {1.75f, 1.75f}) {};
	Player(Game* game, sf::Vector2f startingPosition) : Player(game, startingPosition, 139) {};

	void handleInputs(int deltaTime, sf::Event* event);
	void update(int deltaTime) override;
	bool mustDie() override;

	void downgrade() { --this->evolutionStage; }

	sf::FloatRect getHitBox() const { return this->m_sprite.getGlobalBounds(); }
	
protected:
	float m_jumpStrength = 3.f;
	bool m_isOnGround = false;
	bool m_hasAlreadyJumped = false;
	int evolutionStage = 1;
	
	sf::Vector2f move(sf::Vector2f path) override;
	sf::Vector2f applyGravity(int deltaTime) override;
	void jump();
	void checkForCollisions();

private:
	sf:: Keyboard::Key m_jumpKey = sf::Keyboard::Up;
};

