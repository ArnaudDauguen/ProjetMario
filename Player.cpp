#include "Player.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Game.h"
#include "World.h"
#include "Collider.h"
#include "Enemy.h"

Player::Player(Game* game, sf::Vector2f startingPosition, sf::Vector2f scale, float mass, sf::Vector2f speed)
{
    this->m_game = game;
    if (!this->m_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 11, 0 + 16 * 8, 16, 16)))
	    std::cout << "Issue with loading the player texture" << std::endl;

	this->m_sprite = sf::Sprite(this->m_texture);
	this->m_sprite.setPosition(startingPosition);
	this->m_sprite.scale(scale);
    this->m_mass = mass;
    this->m_speed = speed;
}

Player::Player(Game* game, sf::Vector2f startingPosition)
{
    this->m_game = game;
    if (!this->m_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 11, 0 + 16 * 8, 16, 16)))
	    std::cout << "Issue with loading the player texture" << std::endl;

	this->m_sprite = sf::Sprite(this->m_texture);
	this->m_sprite.setPosition(startingPosition);
	this->m_sprite.scale(1.75f, 1.75f);
    this->m_mass = 1.f;
    this->m_speed = {0.5f, 0.f};
}


void Player::update(int deltaTime)
{
    this->applyGravity(deltaTime);
    this->checkForCollisions();
}


void Player::handleInputs(int deltaTime, sf::Event* event)
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

	// JUMP
    if (sf::Keyboard::isKeyPressed(this->m_jumpKey) && !this->m_hasAlreadyJumped && this->m_isOnGround && this->m_speed.y == 0.f)
    {
	    this->jump();
	    this->m_hasAlreadyJumped = true;
    }
	// if player didnt release jump key, he will infinitely jump, block that
    if (event->type == sf::Event::KeyReleased)
        if (event->key.code == this->m_jumpKey)
            this->m_hasAlreadyJumped = false;
                   

	// todo: replace by a dash
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        const float distance = 4.0f * deltatime * this->m_speed.x;
        this->move({0, distance});
    }

}

sf::Vector2f Player::applyGravity(int deltaTime)
{
	// Abort if no weight
    if (this->m_mass == 0.f)
        return {0.f, 0.f};
	// Apply Jump
    if (this->m_speed.y > 0)
    {
		this->move({ 0.f, -(this->m_speed.y * deltaTime) });
        this->m_speed.y -= this->m_mass * this->m_game->m_gravityStrength * deltaTime * 0.025f;
        this->m_speed.y = std::max(0.f, this->m_speed.y);
    }
	// Standard gravity
    const sf::Vector2f gravityVector = { 0.f, this->m_mass * this->m_game->m_gravityStrength * deltaTime };
    this->move(gravityVector);

    // Check if on ground
    const sf::Vector2f travelableDistance = this->calculateMovementVector(gravityVector);
    this->m_isOnGround = travelableDistance.y == 0.f;
	
    return travelableDistance;
}


sf::Vector2f Player::move(sf::Vector2f path)
{
	// CALCULATE MOVEMENT
    sf::Vector2f travelableDistance = this->calculateMovementVector(path);
	
    if (travelableDistance == sf::Vector2f{ 0, 0 })
        return travelableDistance;
	
	// MOVE
	//check for world translation (right) and move
    const sf::Vector2f playerToWorldOffset = this->m_game->m_world->CheckForWorldMove(this->m_sprite.getPosition(), travelableDistance);
	if(playerToWorldOffset != sf::Vector2f{0, 0})
	{
        sf::Vector2f moveVector = { travelableDistance.x + playerToWorldOffset.x, travelableDistance.y + playerToWorldOffset.y };
        this->m_sprite.move(moveVector);
        this->m_game->m_world->Translate(playerToWorldOffset);
        return moveVector;
	}
	// Standard move if no world translation
    this->m_sprite.move(travelableDistance);
    return travelableDistance;
}

void Player::jump()
{
    this->m_speed.y = this->m_jumpStrength;
    this->m_isOnGround = false;
}

bool Player::mustDie()
{
    return this->evolutionStage <= 0;
}

// check collisions with all other m_enemies in game
void Player::checkForCollisions()
{
    this->calculateDeathCollisionBox();
    sf::FloatRect hitBox = sf::FloatRect(
        this->m_sprite.getGlobalBounds().left,
        this->m_sprite.getGlobalBounds().top + this->m_sprite.getGlobalBounds().height,
        this->m_sprite.getGlobalBounds().width,
        std::min(-2.f, std::max(-2.f, -1.f * this->m_sprite.getGlobalBounds().width * 0.1f))
    );
    for (auto enemy : this->m_game->m_enemies)
    {
        if (enemy->isColliderInKillZone(&hitBox))
        {
            enemy->mustDie(true, this);
            this->jump();
        }
        else if (enemy->isColliding(&this->deathCollisionBox))
        {
            this->downgrade();
        }
    }
}



