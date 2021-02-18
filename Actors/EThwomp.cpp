#include "EThwomp.h"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>


#include "../Game.h"
#include "Player.h"
#include "../World.h"

EThwomp::EThwomp(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale, float mass, float playerDetectionXRange, float timeOnGround, float ascendSpeed)
{
	this->m_game = game;
	this->m_texture = *this->m_game->getTexture(textureIndex);
	this->m_sprite = sf::Sprite(this->m_texture);
	this->m_sprite.setPosition(startingPosition);
	this->m_sprite.scale(scale);
	this->m_mass = mass;
	this->m_speed = {0, 0};

	this->playerDetectionXRange = playerDetectionXRange;
	this->timeOnGround = timeOnGround;
	this->ascendSpeed = ascendSpeed;
	this->startPosition = startingPosition;
	this->buildAgroArea();
}

void EThwomp::update(int deltaTime)
{
	// Detect player
	if(this->m_waitingForPlayer && this->isPlayerInRange())
	{
		this->m_waitingForPlayer = false;
		this->m_isFalling = true;
		return;
	}
	
	// Fall and check ground collision
	if(this->m_isFalling && this->applyGravity(deltaTime) == sf::Vector2f(0.f,0.f))
	{
		this->m_isFalling = false;
		this->timer = this->timeOnGround;
		return;
	}
	
	// Decrease timer
	if(!this->m_waitingForPlayer && !this->m_isFalling && this->timer > 0.f)
	{
		this->timer -= (float)deltaTime;
		return;
	}

	// Go back to startingPosition
	if(!this->m_waitingForPlayer && this->timer <= 0.f)
	{
		sf::Vector2f moveVector = this->move({ 0.f, -1.f * this->ascendSpeed });
		if(this->m_sprite.getPosition().y <= this->startPosition.y + this->m_game->m_world->GetPosition().y || moveVector == sf::Vector2f(0.f, 0.f))
		{
			this->m_waitingForPlayer = true;
		}
	}
	
	
}


sf::Vector2f EThwomp::move(sf::Vector2f path)
{
	// CALCULATE MOVEMENT
	sf::Vector2f travelableDistance = this->calculateMovementVector(path);
	if (travelableDistance == sf::Vector2f(0.f, 0.f))
		this->m_speed *= -1.f;

	// MOVE
	this->m_sprite.move(travelableDistance);
	return travelableDistance;
}

void EThwomp::calculateDeathCollisionBox()
{
	this->deathCollisionBox = sf::FloatRect(
		this->m_sprite.getGlobalBounds().left,
		this->m_sprite.getGlobalBounds().top,
		this->m_sprite.getGlobalBounds().width,
		std::max(2.f, std::min(2.f, this->m_sprite.getGlobalBounds().width * 0.1f))
	);
}

void EThwomp::buildAgroArea()
{
	this->m_agroArea = sf::FloatRect(
		{
			this->m_sprite.getGlobalBounds().left - this->playerDetectionXRange * this->m_game->m_world->getBlockSize(),
			0.f
		}, {
			this->m_sprite.getGlobalBounds().width + 2 * this->playerDetectionXRange * this->m_game->m_world->getBlockSize(),
			(float)this->m_game->m_world->GetSize().y * this->m_game->m_world->getBlockSize()
		}
	);
}


bool EThwomp::isPlayerInRange()
{
	this->buildAgroArea();
	return this->m_game->m_player->getHitBox().intersects(this->m_agroArea);
}

