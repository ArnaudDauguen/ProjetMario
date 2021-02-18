#include "EGoomba.h"

#include <iostream>

#include "../Collider.h"
#include "../World.h"
#include "../Game.h"

EGoomba::EGoomba(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale, float mass, sf::Vector2f speed)
{
	this->m_game = game;
	this->m_texture = *this->m_game->getTexture(textureIndex);
	this->m_sprite = sf::Sprite(this->m_texture);
	this->m_sprite.setPosition(startingPosition);
	this->m_sprite.scale(scale);
	this->m_mass = mass;
	this->m_speed = speed;
}

sf::Vector2f EGoomba::move(sf::Vector2f path)
{
	// CALCULATE MOVEMENT
	sf::Vector2f travelableDistance = this->calculateMovementVector(path);
	if (travelableDistance == sf::Vector2f(0.f, 0.f))
	{
		this->m_speed *= -1.f;
		return travelableDistance;
	}

	// MOVE
	this->m_sprite.move(travelableDistance);

	// Check for holes for next loop
	if(this->isGoingOverAHole(travelableDistance))
		this->m_speed *= -1.f;
	return travelableDistance;
}

void EGoomba::calculateDeathCollisionBox()
{
	this->deathCollisionBox = sf::FloatRect(
		this->m_sprite.getGlobalBounds().left,
		this->m_sprite.getGlobalBounds().top,
		this->m_sprite.getGlobalBounds().width,
		std::max(2.f, std::min(2.f, this->m_sprite.getGlobalBounds().width * 0.1f))
	);
}
