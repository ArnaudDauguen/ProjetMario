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
	sf::Vector2f GetCharacterSize() const {
		return {
		m_sprite.getTexture()->getSize().x * m_sprite.getScale().x,
		m_sprite.getTexture()->getSize().y * m_sprite.getScale().y
		};
	}
	
	void update(int deltaTime) override { this->applyGravity(deltaTime); };
	void draw(sf::RenderWindow& window) override { window.draw(this->m_sprite); };
	bool mustDie() override { return false; }

	void forceMove(sf::Vector2f distance);

protected:
	Game* m_game;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::Vector2f m_speed;
	float m_mass;

	sf::Vector2f calculateMovementVector(sf::Vector2f path);

	virtual void move(sf::Vector2f path);
	virtual void applyGravity(int deltaTime);

private:
	
};

