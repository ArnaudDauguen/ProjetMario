#include "World.h"

#include <iostream>
#include <ostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Enemy.h"
#include "Game.h"
#include "Player.h"


World::World(Game* game, int width, int height, float blockScale) : m_game(game)
{	
    this->m_blockScale = blockScale;
    this->m_size = sf::Vector2i(width, height);
    this->loadTextures();
	
    this->m_blocks = new int* [width];
    for (int i = 0; i < width; ++i)
        this->m_blocks[i] = new int[height];


    for (int j = 0; j < height; ++j)
    {
	    for (int i = 0; i < width; ++i)
	    {
            this->m_blocks[i][j] = -1;

	    	if (j >= 19 && j < 21)
                if(i < 19 || i > 21)
					this->m_blocks[i][j] = 2;

            if (j == 15)
                if (i >= 19 && i <= 21)
                    this->m_blocks[i][j] = 3;
	    	
            if (j >= 21 && j < height - 1)
                this->m_blocks[i][j] = rand() % 2 == 0 ? 0 : 50;
            if (i == width - 1)
                this->m_blocks[i][j] = -1;
	    }
    }

	m_drawingBlockSprite.scale(sf::Vector2f(this->m_game->m_blocScale, this->m_game->m_blocScale));
    
    this->m_rightBoundDistanceInPixels = this->GetSize().x * this->getBlockSize() - this->m_game->GetScreenSize().x;
    this->m_bottomBoundDistanceInPixels = this->GetSize().y * this->getBlockSize() - this->m_game->GetScreenSize().y;
}

void World::Translate(sf::Vector2f distance)
{
    this->m_position.x += distance.x;
    this->m_position.y += distance.y;

    for (const auto& enemy : this->m_game->m_enemies)
    {
        enemy->forceMove(distance);
    }
}


void World::draw(sf::RenderWindow& window)
{
    float bgX = 0.f;
	for (int i = 0; i < 3; ++i)
	{
        bgX = this->GetPosition().x - (1.2f - 0.3f * i) * (this->GetPosition().x / this->GetSize().x * 16 * this->m_game->m_blocScale);

        this->m_backgrounds[i].setTexture(this->m_backgroundTextures[i]);
		this->m_backgrounds[i].setPosition(bgX, this->GetPosition().y);
        window.draw(m_backgrounds[i]);
	}

    const sf::Vector2i topLeftBlock = this->PositionOnScreenToMapBlockIndex({ 0.f, 0.f });
	const sf::Vector2i bottomRightBlock = this->PositionOnScreenToMapBlockIndex({ (float)this->m_game->GetScreenSize().x, (float)this->m_game->GetScreenSize().y });
	
    for (int y = topLeftBlock.y -1; y < bottomRightBlock.y +1; y++) {
        for (int x = topLeftBlock.x -1; x < bottomRightBlock.x +1; x++) {
            if (x < 0 || y < 0 || x > this->GetSize().x -1 || y > this->GetSize().y -1) continue;
            if (this->m_blocks[x][y] == -1) continue;

            //blockSprite.setTexture(this->m_blocks[j][i] == 1 ? m_dirt_texture : m_stone_texture);
            m_drawingBlockSprite.setTexture(this->m_blockTextures[this->m_blocks[x][y]]);

            m_drawingBlockSprite.setPosition(x * (16 * this->m_game->m_blocScale) + this->GetPosition().x, y * (16 * this->m_game->m_blocScale) + this->GetPosition().y);

            window.draw(m_drawingBlockSprite);
        }
    }
}

void World::loadTextures()
{
	for (int y = 0; y < float((this->m_blockTextureCount -1)/16); ++y)
	{
		for (int x = 0; x < 16; ++x)
		{
            if (!this->m_blockTextures[y * 16 + x].loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * x, 0 + 16 * y, 16, 16)))
                std::cout << "Issue with loading the m_world texture " << y*16 + x << std::endl;
		}
	}

    for (int i = 0; i < 3; ++i)
    {
        std::string filePath = "Textures/Backgrounds/layer_0" + std::to_string(i + 1) + ".png";
        if (!this->m_backgroundTextures[i].loadFromFile(filePath))
            std::cout << "Issue with loading the background texture '" + filePath + "'" << std::endl;
    }
}


sf::Vector2f World::PositionOnScreenToMapPosition(sf::Vector2f positionOnScreen) const
{
    return { positionOnScreen.x - this->m_position.x, positionOnScreen.y - this->m_position.y };
}

sf::Vector2i World::PositionOnMapToMapBlockIndex(sf::Vector2f positionOnMap) const
{
    const float blockSize = this->m_baseBlockSize * this->m_game->m_blocScale;
    return { (int)floor(positionOnMap.x / blockSize), (int)floor(positionOnMap.y / blockSize) };
}

sf::Vector2i World::PositionOnScreenToMapBlockIndex(sf::Vector2f positionOnMap) const
{
    const float blockSize = this->m_baseBlockSize * this->m_game->m_blocScale;
    return { (int)floor((positionOnMap.x - this->m_position.x) / blockSize), (int)floor((positionOnMap.y - this->m_position.y) / blockSize) };
}

sf::Vector2f World::CheckForWorldMove(sf::Vector2f playerPosition, sf::Vector2f travelableDistance)
{
    sf::Vector2f worldMove = { 0, 0 };
    float xPlayerLocation = playerPosition.x + travelableDistance.x;
    float yPlayerLocation = playerPosition.y + travelableDistance.y;
    //check for right
    if (xPlayerLocation + this->m_game->m_player->GetCharacterSize().x > (this->m_game->GetScreenSize().x * this->m_rightBoundOnMap))
    { // and check to hide right black pixels
    	if(this->m_position.x > -m_rightBoundDistanceInPixels)
    	{
            worldMove.x = (this->m_game->GetScreenSize().x * this->m_rightBoundOnMap) - (xPlayerLocation + this->m_game->m_player->GetCharacterSize().x);
    	}else
    	{
            worldMove.x = -m_rightBoundDistanceInPixels - this->m_position.x;
    	}
    }

    //check for left
    else if (xPlayerLocation < (this->m_game->GetScreenSize().x * this->m_leftBoundOnMap))
    { // and check to hide left black pixels
    	if(this->m_position.x < 0)
    	{
			worldMove.x = (this->m_game->GetScreenSize().x * this->m_leftBoundOnMap) - xPlayerLocation;
    	}else
    	{
            worldMove.x = 0 - this->m_position.x;
    	}
    }

    //check for bottom
    if (yPlayerLocation > (this->m_game->GetScreenSize().y * this->m_bottomBoundOnMap))
    { // and check to hide bottom black pixels
        if (this->m_position.y > -m_bottomBoundDistanceInPixels)
        {
            worldMove.y = (this->m_game->GetScreenSize().y * this->m_bottomBoundOnMap) - yPlayerLocation;
        }else
        {
            worldMove.y = -m_bottomBoundDistanceInPixels - this->m_position.y;
        }
    }

    //check for top
    else if (yPlayerLocation < (this->m_game->GetScreenSize().y * this->m_topBoundOnMap))
    { // and check to hide top black pixels
    	if(this->m_position.y < 0)
    	{
            worldMove.y = (this->m_game->GetScreenSize().y * this->m_topBoundOnMap) - yPlayerLocation;
    	}else
    	{
            worldMove.y = 0 - this->m_position.y;
    	}
    }


    return worldMove;
}
