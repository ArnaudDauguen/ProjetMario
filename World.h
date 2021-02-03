#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "IDrawableObject.h"

class Game;

class World : public IDrawableObject
{
public:
	World(Game* game, int width, int height);
	
	void draw(sf::RenderWindow& window) override;

	void Translate(float distance);

	sf::Vector2f PositionOnScreenToMapPosition(sf::Vector2f positionOnScreen) const ;
	sf::Vector2i PositionOnMapToMapBlockIndex(sf::Vector2f positionOnMap) const ;
	sf::Vector2i PositionOnScreenToMapBlockIndex(sf::Vector2f positionOnMap) const ;
	
	sf::Vector2f GetPosition() const { return m_position; }
	sf::Vector2i GetSize() const { return m_size; }
	int** GetBlocks() const { return m_blocks; }

	bool mustDie() override { return false; }

	const int BlockSize = 16;
private:
	Game* m_game;
	
	sf::Vector2i m_size = sf::Vector2i(0, 0);

	sf::Vector2f m_position = sf::Vector2f(0, 0);

	int** m_blocks;

	sf::Texture m_player_texture;
	const int blockTextureCount = 256;
	sf::Texture m_blockTextures[256];

	void loadTextures();
};

