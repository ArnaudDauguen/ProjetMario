#include "EGoomba.h"

#include <iostream>

EGoomba::EGoomba(Game* game, int x, int y, float scale, float mass, int textureIndex)
{
	this->m_game = game;
	if (!this->m_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0, 0, 16, 16)))
		std::cout << "Issue with loading the player texture" << std::endl;

	this->m_sprite = sf::Sprite(this->m_texture);
	this->m_sprite.setPosition(x, y);
	this->m_sprite.scale(sf::Vector2f(scale, scale));
	this->m_mass = mass;
}

void EGoomba::update(int deltaTime)
{
	if (this->mustDie())
		return;

	return;
	
	this->move({ 1.f * deltaTime, 0.f });
}
