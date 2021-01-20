#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Game;

class World
{
public:
	World(Game* game, int width, int height);
	
	void draw(sf::RenderWindow& window);

	void Translate(float distance);
	
	sf::Vector2f GetPosition() const { return m_position; }
	sf::Vector2i GetSize() const { return m_size; }
	int** GetBlocks() const { return m_blocks; }

	const int BlockSize = 16;
private:
	Game* m_game;
	
	sf::Vector2i m_size = sf::Vector2i(0, 0);

	sf::Vector2f m_position = sf::Vector2f(0, 0);

	int** m_blocks;

	sf::Texture m_dirt_texture;
	sf::Texture m_stone_texture;
};

