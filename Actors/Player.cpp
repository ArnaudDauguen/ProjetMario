#include "Player.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Game.h"
#include "../World.h"
#include "../Collider.h"
#include "../Enemy.h"

Player::Player(Game* game, sf::Vector2f startingPosition, int textureIndex, sf::Vector2f scale, float mass, sf::Vector2f speed)
{
    this->m_game = game;
    this->m_texture = *this->m_game->getTexture(textureIndex);
	this->m_sprite = sf::Sprite(this->m_texture);
	this->m_sprite.setPosition(startingPosition);
	this->m_sprite.scale(scale);
    this->m_mass = mass;
    this->m_speed = speed;
}

void Player::update(int deltaTime)
{
    this->applyGravity(deltaTime);
    this->checkForCollisions();
}

void Player::handleInputs(int deltaTime, sf::Event* event)
{
    if (this->m_isDead)
        return;
	
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
    bool isTouchingVictoryBlock = false;
    sf::Vector2f travelableDistance = this->calculateMovementVector(path, &isTouchingVictoryBlock);
    if (isTouchingVictoryBlock)
        this->m_game->m_world->FinishLevel();
	
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
    this->m_isDead =
        this->evolutionStage <= 0
        || this->m_game->m_world->PositionOnScreenToMapBlockIndex(this->m_sprite.getPosition()).y >= this->m_game->m_world->GetSize().y - 1;
    return this->m_isDead;
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



