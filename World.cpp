#include "World.h"


#include <iostream>
#include <ostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Game.h"


World::World(Game* game, int width, int height) : m_game(game)
{
    this->m_size = sf::Vector2i(width, height);
	
    this->m_blocks = new int* [height];
    for (int i = 0; i < height; ++i)
        this->m_blocks[i] = new int[width];


    for (int j = 0; j < height; ++j)
    {
	    for (int i = 0; i < width; ++i)
	    {
            this->m_blocks[j][i] = 0;

	    	if (j >= 19 && j < 21)
                this->m_blocks[j][i] = 1;
	    	
            if (j >= 21 && j < height)
                this->m_blocks[j][i] = 2;
	    }
    }

    if (!this->m_dirt_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 2, 0 + 16 * 0, 16, 16)))
        std::cout << "Issue with loading the world texture 1" << std::endl;
    
    if (!this->m_stone_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 0, 0 + 16 * 0, 16, 16)))
        std::cout << "Issue with loading the world texture 2" << std::endl;
}

void World::Translate(float distance)
{
    this->m_position.x += distance;
}


void World::draw(sf::RenderWindow& window)
{
    for (int j = 0; j < this->GetSize().y; j++) {
        for (int i = 0; i < this->GetSize().x; i++) {
            if (this->m_blocks[j][i] == 0) continue;

            sf::Sprite dirt_sprite(this->m_blocks[j][i] == 1 ? m_dirt_texture : m_stone_texture);

            dirt_sprite.scale(sf::Vector2f(this->m_game->Scale, this->m_game->Scale));
        	
            dirt_sprite.setPosition(i * (16 * this->m_game->Scale) + this->GetPosition().x, j * (16 * this->m_game->Scale) + this->GetPosition().y);

            window.draw(dirt_sprite);
        }
    }
}
