#include "Player.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Game.h"
#include "World.h"

Player::Player(Game* game, int x, int y, float scale)
{
    this->m_game = game;
    if (!this->m_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 0, 0 + 16 * 0, 16, 16)))
	    std::cout << "Issue with loading the player texture" << std::endl;

	m_sprite = sf::Sprite(this->m_texture);
	m_sprite.setPosition(x, y);
	m_sprite.scale(sf::Vector2f (scale, scale));
}

void Player::handleInputs(int deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        int distance = 1.f * deltaTime * this->m_speed;

        sf::Vector2f playerPosition = this->m_sprite.getPosition();
    	
    	if (playerPosition.x - distance < (this->m_game->GetScreenSize().x * 1 / 4))
    	{
            m_sprite.setPosition(this->m_game->GetScreenSize().x * 1 / 4, playerPosition.y);
            this->m_game->world->Translate(distance);
    	} else {
            m_sprite.move(-distance, 0.f);
    	}
    }
	
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        int distance = 1.f * deltaTime * this->m_speed;

        sf::Vector2f playerPosition = this->m_sprite.getPosition();
    	
        if (playerPosition.x + distance > (this->m_game->GetScreenSize().x * 3 / 4))
        {
            m_sprite.setPosition(this->m_game->GetScreenSize().x * 3 / 4, playerPosition.y);
            this->m_game->world->Translate(-distance);
        }
        else {
            m_sprite.move(distance, 0.f);
        }
    }

	
	// todo: replace by a jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_sprite.move(0.0f, -1.0f * deltaTime * this->m_speed);
    }
}

void Player::update(int deltaTime)
{
    // "Gravity"
    // int falling = this->TryMoveDown(this->m_speed * deltaTime);
	int falling = this->TryMoveDown(0.2f * deltaTime);
    this->m_sprite.move(0.0f, falling);
}


void Player::draw(sf::RenderWindow& window) const
{
    window.draw(this->m_sprite);
}


// once moved to class, some args will no longer be mandatory
int Player::TryMoveDown(float distance) {
    sf::Vector2f playerSize = this->GetCharacterSize();
    int blockSize = this->m_game->world->BlockSize * this->m_game->Scale;
	
    float screenPosX = m_sprite.getPosition().x;
    float screenPosY = m_sprite.getPosition().y;

    // getting the two down corners
    const sf::Vector2f firstCornerPosition = this->m_game->world->PositionOnScreenToMapPosition({screenPosX, screenPosY + playerSize.y}); // bottom left
    const sf::Vector2f secondCornerPosition = this->m_game->world->PositionOnScreenToMapPosition({ screenPosX + playerSize.x, screenPosY + playerSize.y }); // bottom right

    // convert positions to squares on map
    const sf::Vector2i firstCornerSquare = this->m_game->world->PositionOnMapToMapBlockIndex(firstCornerPosition);
    const sf::Vector2i secondCornerSquare = this->m_game->world->PositionOnMapToMapBlockIndex(secondCornerPosition);
    const bool isAboveOnlyOneBlock = firstCornerSquare.x == secondCornerSquare.x;
	
    //printf("fst point [%d;%d]\n", firstCornerSquare.x, firstCornerSquare.y);
    //printf("scd point [%d;%d]\n\n", secondCornerSquare.x, secondCornerSquare.y);

    //Try moving // direction Down : y++
    bool blocked = false;
    int blockingBlocIndex = 0;

    int** worldBlocks = this->m_game->world->GetBlocks();
	sf::Vector2i worldSize = this->m_game->world->GetSize();
    for (int blocIndexInPath = 0; blocIndexInPath < ceil(distance / blockSize); blocIndexInPath++) {
        int blocIndexToTest = firstCornerSquare.y + blocIndexInPath;
        if (!(blocIndexToTest >= worldSize.y || blocIndexToTest < 0 || firstCornerSquare.x >= worldSize.x || firstCornerSquare.x < 0)) {
	        if (worldBlocks[blocIndexToTest][firstCornerSquare.x] != -1) {
	            blocked = true;
	            blockingBlocIndex = blocIndexToTest;
	        }
        }

        //if above two distinct blocs
        if (!isAboveOnlyOneBlock) {
            if (!(blocIndexToTest >= worldSize.y || blocIndexToTest < 0 || secondCornerSquare.x >= worldSize.x || secondCornerSquare.x < 0)) {
                if (worldBlocks[blocIndexToTest][secondCornerSquare.x] != -1) {
                    blocked = true;
                    blockingBlocIndex = blocIndexToTest;
                }
            }
        }
    }
    float travelDistanceReal = blocked
        ? (blockingBlocIndex * (int)blockSize) - firstCornerPosition.y //- squareOnMapSize
        : distance;

    return travelDistanceReal;
}

