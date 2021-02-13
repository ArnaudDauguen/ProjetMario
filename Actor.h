#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "Game.h"


class Actor
{
public:
	sf::Vector2f GetCharacterSize() const {
		return {
		m_sprite.getTexture()->getSize().x * m_sprite.getScale().x,
		m_sprite.getTexture()->getSize().y * m_sprite.getScale().y
		};
	}

protected:
	Game* m_game;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	float m_speed = 0.5f;

	sf::Vector2f calculateMovementVector(sf::Vector2f path);

	virtual void move(sf::Vector2f path);

private:
	
};

