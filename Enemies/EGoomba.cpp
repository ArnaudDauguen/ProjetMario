#include "EGoomba.h"

#include <iostream>

EGoomba::EGoomba(Game* game, sf::Vector2f startingPosition, sf::Vector2f scale, float mass, int textureIndex, sf::Vector2f speed)
{
	this->m_game = game;
	if (!this->m_texture.loadFromFile("Textures/terrain.png", sf::IntRect(16 * (textureIndex%16), 16 * (int)floor(textureIndex / 16), 16, 16)))
		std::cout << "Issue with loading the Goombat texture" << std::endl;
	//TODO to avoid blanck bounds, use a sf::Image and Image.CreateMaskFromColor(sf::Color(0, 255, 0, 255), 0)
	this->m_sprite = sf::Sprite(this->m_texture);
	this->m_sprite.setPosition(startingPosition);
	this->m_sprite.scale(scale);
	this->m_mass = mass;
	this->m_speed = speed;
}
EGoomba::EGoomba(Game* game, sf::Vector2f startingPosition, int textureIndex)
{
	this->m_game = game;
	if (!this->m_texture.loadFromFile("Textures/terrain.png", sf::IntRect(16 * (textureIndex%16), 16 * (int)floor(textureIndex / 16), 16, 16)))
		std::cout << "Issue with loading the Goombat texture" << std::endl;
	//TODO to avoid blanck bounds, use a sf::Image and Image.CreateMaskFromColor(sf::Color(0, 255, 0, 255), 0)
	this->m_sprite = sf::Sprite(this->m_texture);
	this->m_sprite.setPosition(startingPosition);
	this->m_sprite.scale(1.75f, 1.75f);
	this->m_mass = 1.f;
	this->m_speed = {0.1f, 0.f};
}


sf::Vector2f EGoomba::move(sf::Vector2f path)
{
	// CALCULATE MOVEMENT
	sf::Vector2f travelableDistance = this->calculateMovementVector(path);
	if (travelableDistance == sf::Vector2f(0.f, 0.f))
		this->m_speed *= -1.f;

	// MOVE
	this->m_sprite.move(travelableDistance);
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
