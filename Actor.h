#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "IDrawableObject.h"
#include "IUpdatableObject.h"

class Game;

class Actor : public IDrawableObject, public IUpdatableObject
{
public:
	sf::FloatRect deathCollisionBox;
	
	sf::Vector2f GetCharacterSize() const {
		return {
		m_sprite.getTexture()->getSize().x * m_sprite.getScale().x,
		m_sprite.getTexture()->getSize().y * m_sprite.getScale().y
		};
	}
	
	void update(int deltaTime) override { this->applyGravity(deltaTime); };
	void draw(sf::RenderWindow& window) override;
	bool mustDie() override { return m_isDead; }

	virtual bool isColliding(sf::FloatRect* globalBoundToTest);
	virtual bool isColliderInKillZone(sf::FloatRect* globalBoundToTest);
	virtual void calculateDeathCollisionBox();

	void forceMove(sf::Vector2f distance);
	void mustDie(bool mustDie, Actor* killer) { this->m_isDead = mustDie; }
	bool isDead() const { return this->m_isDead; }

protected:
	Game* m_game;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::Vector2f m_speed;
	float m_mass;
	bool m_isDead = false;

	sf::Vector2f calculateMovementVector(sf::Vector2f path, bool* isTouchingVictoryBlock);
	sf::Vector2f calculateMovementVector(sf::Vector2f path);

	virtual sf::Vector2f move(sf::Vector2f path);
	virtual sf::Vector2f applyGravity(int deltaTime);
	virtual bool isGoingOverAHole(sf::Vector2f direction);

private:
	
};

