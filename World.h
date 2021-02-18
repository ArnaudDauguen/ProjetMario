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
	bool mustDie() override { return false; }

	void FinishLevel() { this->isComplete = true; }
	bool isLevelComplete() const { return this->isComplete; }

	void Translate(sf::Vector2f distance);

	sf::Vector2f PositionOnScreenToMapPosition(sf::Vector2f positionOnScreen) const;
	sf::Vector2i PositionOnMapToMapBlockIndex(sf::Vector2f positionOnMap) const;
	sf::Vector2i PositionOnScreenToMapBlockIndex(sf::Vector2f positionOnMap) const;

	sf::Vector2f CheckForWorldMove(sf::Vector2f playerPosition, sf::Vector2f travelableDistance);

	sf::Vector2f GetPosition() const { return m_position; }
	sf::Vector2i GetSize() const { return m_size; }
	int** GetBlocks() const { return m_blocks; }
	int GetBlock(int x, int y) const { return m_blocks[x][y]; }
	int GetBlock(sf::Vector2i pos) const { return m_blocks[pos.x][pos.y]; }
	float getBlockSize() const { return this->m_baseBlockSize * this->m_blockScale; }

private:
	Game* m_game;

	bool isComplete = false;

	const int m_baseBlockSize = 16;
	float m_blockScale;

	sf::Vector2i m_size = sf::Vector2i(0, 0);
	sf::Vector2f m_position = sf::Vector2f(0, 0);

	int** m_blocks;

	sf::Sprite m_drawingBlockSprite;

	int m_backgroundLenght = 3;
	sf::Sprite m_backgrounds[3];
	sf::Texture m_backgroundTextures[3];

	const float m_leftBoundOnMap = 0.25f;
	const float m_rightBoundOnMap = 0.75f;
	const float m_topBoundOnMap = 0.3f;
	const float m_bottomBoundOnMap = 0.7f;
	float m_rightBoundDistanceInPixels;
	float m_bottomBoundDistanceInPixels;

	void loadAllTextures();
};

