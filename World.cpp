#include "World.h"


#include "math.h"
#include <iostream>
#include <ostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Game.h"


World::World(Game* game, int width, int height) : m_game(game)
{
    this->m_size = sf::Vector2i(width, height);
    this->loadTextures();
	
    this->m_blocks = new int* [height];
    for (int i = 0; i < height; ++i)
        this->m_blocks[i] = new int[width];


    for (int j = 0; j < height; ++j)
    {
	    for (int i = 0; i < width; ++i)
	    {
            this->m_blocks[j][i] = -1;

	    	if (j >= 19 && j < 21)
                if(i < 19 || i > 21)
					this->m_blocks[j][i] = 2;

            if (j == 15)
                if (i >= 19 && i <= 21)
                    this->m_blocks[j][i] = 3;
	    	
            if (j >= 21 && j < height)
                this->m_blocks[j][i] = rand() % 2 == 0 ? 0 : 50;
	    }
    }

    /*if (!this->m_dirt_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 2, 0 + 16 * 0, 16, 16)))
        std::cout << "Issue with loading the world texture 1" << std::endl;
    
    if (!this->m_stone_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 0, 0 + 16 * 0, 16, 16)))
        std::cout << "Issue with loading the world texture 2" << std::endl;*/
}

void World::Translate(float distance)
{
    this->m_position.x += distance;
}


void World::draw(sf::RenderWindow& window)
{
    sf::Sprite blockSprite;
    blockSprite.scale(sf::Vector2f(this->m_game->Scale, this->m_game->Scale));
    for (int j = 0; j < this->GetSize().y; j++) {
        for (int i = 0; i < this->GetSize().x; i++) {
            if (this->m_blocks[j][i] == -1) continue;
            
            //blockSprite.setTexture(this->m_blocks[j][i] == 1 ? m_dirt_texture : m_stone_texture);
            blockSprite.setTexture(this->m_blockTextures[this->m_blocks[j][i]]);
        	
            blockSprite.setPosition(i * (16 * this->m_game->Scale) + this->GetPosition().x, j * (16 * this->m_game->Scale) + this->GetPosition().y);

            window.draw(blockSprite);
        }
    }
}

void World::loadTextures()
{
	for (int y = 0; y < float((this->blockTextureCount -1)/16); ++y)
	{
		for (int x = 0; x < 16; ++x)
		{
            if (!this->m_blockTextures[y * 16 + x].loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * x, 0 + 16 * y, 16, 16)))
                std::cout << "Issue with loading the world texture " << y*16 + x << std::endl;
		}
	}
}


sf::Vector2f World::PositionOnScreenToMapPosition(sf::Vector2f positionOnScreen) const
{
    return { positionOnScreen.x - this->GetPosition().x, positionOnScreen.y - this->GetPosition().y };
}

sf::Vector2i World::PositionOnMapToMapBlockIndex(sf::Vector2f positionOnMap) const
{
    const float blockSize = this->BlockSize * this->m_game->Scale;
    return { (int)floor(positionOnMap.x / blockSize), (int)floor(positionOnMap.y / blockSize) };
}

sf::Vector2i World::PositionOnScreenToMapBlockIndex(sf::Vector2f positionOnMap) const
{
    const float blockSize = this->BlockSize * this->m_game->Scale;
    return { (int)floor((positionOnMap.x - this->GetPosition().x) / blockSize), (int)floor((positionOnMap.y - this->GetPosition().y) / blockSize) };
}
