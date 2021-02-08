#include "Player.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Game.h"
#include "World.h"
#include "Collider.h"

Player::Player(Game* game, int x, int y, float scale)
{
    this->m_game = game;
    if (!this->m_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 11, 0 + 16 * 8, 16, 16)))
	    std::cout << "Issue with loading the player texture" << std::endl;

	this->m_sprite = sf::Sprite(this->m_texture);
	this->m_sprite.setPosition(x, y);
	this->m_sprite.scale(sf::Vector2f (scale, scale));
}

void Player::handleInputs(int deltaTime)
{
    float deltatime = float(deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        const float distance = -1.f * deltatime * this->m_speed;
        this->move({ distance, 0 });
    }
	
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        const float distance = 1.f * deltatime * this->m_speed;
        this->move({ distance, 0 });
    }

	// todo: replace by a jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        const float distance = -2.0f * deltatime * this->m_speed;
        this->move({ 0, distance });
    }

	// todo: replace by a dash
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        const float distance = 4.0f * deltatime * this->m_speed;
        this->move({0, distance});
    }

}

void Player::update(int deltaTime)
{
    // "Gravity"
	// NEW collision detection system
    this->move({ 0.f, 0.2f * deltaTime });
}


void Player::draw(sf::RenderWindow& window)
{
    window.draw(this->m_sprite);
}

void Player::move(sf::Vector2f path)
{
	// CALCULATE MOVEMENT
	// Get collision data
    std::vector<sf::Vector2i> firstCornerBlockOnPath = {};
    std::vector<sf::Vector2i> secondCornerBlockOnPath = {};
    std::vector<sf::Vector2i> thirdCornerBlockOnPath = {};
    std::vector<sf::Vector2i> fourthCornerBlockOnPath = {};
    const int numberOfStep = ceil(float(sqrt(path.x * path.x + path.y * path.y)) / this->m_game->m_world->getBlockSize()) * 2;
    Collider::getMapBlockOnPath(&numberOfStep, this->m_game->m_world, this->m_sprite.getPosition(), this->GetCharacterSize().x, this->GetCharacterSize().y, path,
        &firstCornerBlockOnPath,
        &secondCornerBlockOnPath,
        &thirdCornerBlockOnPath,
        &fourthCornerBlockOnPath);

	// Calculate travelable distance
    sf::Vector2f travelableDistance = { 0, 0 };
    const sf::Vector2f stepDistance = { path.x / numberOfStep, path.y / numberOfStep };
    for (int step = 0; step < numberOfStep; ++step)
    {
        if (
            // Check if target block is in map
            firstCornerBlockOnPath[step].x >= 0 && secondCornerBlockOnPath[step].x >= 0 && thirdCornerBlockOnPath[step].x >= 0 && fourthCornerBlockOnPath[step].x >= 0
            && firstCornerBlockOnPath[step].x < this->m_game->m_world->GetSize().x && secondCornerBlockOnPath[step].x < this->m_game->m_world->GetSize().x && thirdCornerBlockOnPath[step].x < this->m_game->m_world->GetSize().x && fourthCornerBlockOnPath[step].x < this->m_game->m_world->GetSize().x
            && firstCornerBlockOnPath[step].y >= 0 && secondCornerBlockOnPath[step].y >= 0 && thirdCornerBlockOnPath[step].y >= 0 && fourthCornerBlockOnPath[step].y >= 0
            && firstCornerBlockOnPath[step].y < this->m_game->m_world->GetSize().y && secondCornerBlockOnPath[step].y < this->m_game->m_world->GetSize().y && thirdCornerBlockOnPath[step].y < this->m_game->m_world->GetSize().y && fourthCornerBlockOnPath[step].y < this->m_game->m_world->GetSize().y
            // Check if target block is valid destination
            && this->m_game->m_world->GetBlocks()[firstCornerBlockOnPath[step].x][firstCornerBlockOnPath[step].y] == -1
            && this->m_game->m_world->GetBlocks()[secondCornerBlockOnPath[step].x][secondCornerBlockOnPath[step].y] == -1
            && this->m_game->m_world->GetBlocks()[thirdCornerBlockOnPath[step].x][thirdCornerBlockOnPath[step].y] == -1
            && this->m_game->m_world->GetBlocks()[fourthCornerBlockOnPath[step].x][fourthCornerBlockOnPath[step].y] == -1
        ) travelableDistance += stepDistance;
        else break;
    }

	// MOVE

	//check for world translation (right) and move
    const sf::Vector2f playerPosition = this->m_sprite.getPosition();
    if (playerPosition.x + travelableDistance.x > (this->m_game->GetScreenSize().x * 3 / 4))
    {
        const float playerToWorldOffset = (this->m_game->GetScreenSize().x * 3 / 4) - (playerPosition.x + travelableDistance.x);
        this->m_game->m_world->Translate(playerToWorldOffset);
        this->m_sprite.move({ travelableDistance.x + playerToWorldOffset, travelableDistance.y });
        return;
    }

	//check for world translation (right) and move
    if (playerPosition.x + travelableDistance.x < (this->m_game->GetScreenSize().x * 1 / 4))
    {
        const float playerToWorldOffset = (this->m_game->GetScreenSize().x * 1 / 4) - (playerPosition.x + travelableDistance.x);
        this->m_game->m_world->Translate(playerToWorldOffset);
        this->m_sprite.move({ travelableDistance.x + playerToWorldOffset, travelableDistance.y });
        return;
    }

	// Standard move if no world translation
    this->m_sprite.move(travelableDistance);
}

