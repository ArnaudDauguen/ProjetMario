#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "IDrawableObject.h"

class Game;

class World : public IDrawableObject
{
public:
	World(Game* game, int width, int height, float blockScale);
	
	void draw(sf::RenderWindow& window) override;

	void Translate(sf::Vector2f distance);

	sf::Vector2f PositionOnScreenToMapPosition(sf::Vector2f positionOnScreen) const ;
	sf::Vector2i PositionOnMapToMapBlockIndex(sf::Vector2f positionOnMap) const ;
	sf::Vector2i PositionOnScreenToMapBlockIndex(sf::Vector2f positionOnMap) const ;

	sf::Vector2f CheckForWorldMove(sf::Vector2f playerPosition, sf::Vector2f travelableDistance);
	
	sf::Vector2f GetPosition() const { return m_position; }
	sf::Vector2i GetSize() const { return m_size; }
	int** GetBlocks() const { return m_blocks; }
	int GetBlock(int x, int y) const { return m_blocks[x][y]; }
	float getBlockSize() const { return this->m_baseBlockSize * this->m_blockScale; }
	bool mustDie() override { return false; }

private:
	Game* m_game;
	
	const int m_baseBlockSize = 16;
	float m_blockScale;
	
	sf::Vector2i m_size = sf::Vector2i(0, 0);
	sf::Vector2f m_position = sf::Vector2f(0, 0);

	int** m_blocks;

	sf::Sprite m_drawingBlockSprite;
	const int m_blockTextureCount = 256;
	sf::Texture m_blockTextures[256];

	const float m_leftBoundOnMap = 0.25f;
	const float m_rightBoundOnMap = 0.75f;
	const float m_topBoundOnMap = 0.3f;
	const float m_bottomBoundOnMap = 0.7f;
	float m_leftBoundDistanceInPixels;
	float m_bottomBoundDistanceInPixels;

	void loadTextures();
};

