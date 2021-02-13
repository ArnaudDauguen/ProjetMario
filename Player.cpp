#include "Player.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Game.h"
#include "World.h"
#include "Collider.h"

Player::Player(Game* game, int x, int y, float scale, float mass, sf::Vector2f speed)
{
    this->m_game = game;
    if (!this->m_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 11, 0 + 16 * 8, 16, 16)))
	    std::cout << "Issue with loading the player texture" << std::endl;

	this->m_sprite = sf::Sprite(this->m_texture);
	this->m_sprite.setPosition(x, y);
	this->m_sprite.scale(sf::Vector2f (scale, scale));
    this->m_mass = mass;
    this->m_speed = speed;
}

void Player::handleInputs(int deltaTime)
{
    float deltatime = float(deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        const float distance = -1.f * deltatime * this->m_speed.x;
        this->move({ distance, 0 });
    }
	
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        const float distance = 1.f * deltatime * this->m_speed.x;
        this->move({ distance, 0 });
    }

	// todo: replace by a jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        const float distance = -2.0f * deltatime * this->m_speed.x;
        this->move({ 0, distance });
    }

	// todo: replace by a dash
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        const float distance = 4.0f * deltatime * this->m_speed.x;
        this->move({0, distance});
    }

}

void Player::applyGravity(int deltaTime)
{
    if (this->m_mass == 0.f)
        return;

    this->move({ 0.f, this->m_mass * this->m_game->gravityStrength * deltaTime });
}


void Player::move(sf::Vector2f path)
{
	// CALCULATE MOVEMENT
    sf::Vector2f travelableDistance = this->calculateMovementVector(path);
    if (travelableDistance == sf::Vector2f{ 0, 0 })
        return;
	
	// MOVE
	//check for world translation (right) and move
    const sf::Vector2f playerToWorldOffset = this->m_game->m_world->CheckForWorldMove(this->m_sprite.getPosition(), travelableDistance);
	if(playerToWorldOffset != sf::Vector2f{0, 0})
	{
        this->m_sprite.move({ travelableDistance.x + playerToWorldOffset.x, travelableDistance.y + playerToWorldOffset.y });
        this->m_game->m_world->Translate(playerToWorldOffset);
        return;
	}
	// Standard move if no world translation
    this->m_sprite.move(travelableDistance);
}

