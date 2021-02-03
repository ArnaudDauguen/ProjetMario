#include "World.h"


#include "math.h"
#include <iostream>
#include <ostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Game.h"


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
	    	
            if (j >= 21 && j < height)
                this->m_blocks[i][j] = rand() % 2 == 0 ? 0 : 50;
	    }
    }

	m_drawingBlockSprite.scale(sf::Vector2f(this->m_game->m_blocScale, this->m_game->m_blocScale));

    /*if (!this->m_dirt_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 2, 0 + 16 * 0, 16, 16)))
        std::cout << "Issue with loading the m_world texture 1" << std::endl;
    
    if (!this->m_stone_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 0, 0 + 16 * 0, 16, 16)))
        std::cout << "Issue with loading the m_world texture 2" << std::endl;*/
}

void World::Translate(float distance)
{
    this->m_position.x += distance;
}


void World::draw(sf::RenderWindow& window)
{
    for (int y = 0; y < this->GetSize().y; y++) {
        for (int x = 0; x < this->GetSize().x; x++) {
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
}


sf::Vector2f World::PositionOnScreenToMapPosition(sf::Vector2f positionOnScreen) const
{
    return { positionOnScreen.x - this->GetPosition().x, positionOnScreen.y - this->GetPosition().y };
}

sf::Vector2i World::PositionOnMapToMapBlockIndex(sf::Vector2f positionOnMap) const
{
    const float blockSize = this->m_baseBlockSize * this->m_game->m_blocScale;
    return { (int)floor(positionOnMap.x / blockSize), (int)floor(positionOnMap.y / blockSize) };
}

sf::Vector2i World::PositionOnScreenToMapBlockIndex(sf::Vector2f positionOnMap) const
{
    const float blockSize = this->m_baseBlockSize * this->m_game->m_blocScale;
    return { (int)floor((positionOnMap.x - this->GetPosition().x) / blockSize), (int)floor((positionOnMap.y - this->GetPosition().y) / blockSize) };
}
