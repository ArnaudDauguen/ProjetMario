#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>


#include "BlocksData.h"
#include "IDrawableObject.h"
#include "LevelData.h"
#include "Messager.h"

class Game;

class World : public IDrawableObject
{
public:
	World(Game* game, float blockScale);

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
	sf::Vector2i GetSize() const { return { m_levelData.width, m_levelData.height }; }

	std::vector<std::vector<int>> GetBlocks() const { return m_levelData.data; }
	BlockData GetBlock(int x, int y) const { return this->getBlockFromId(m_levelData.data[y][x]); }
	BlockData GetBlock(sf::Vector2i pos) const { return this->GetBlock(pos.x, pos.y); }
	int GetBlockId(int x, int y) const { return m_levelData.data[y][x]; }
	int GetBlockId(sf::Vector2i pos) const { return this->GetBlockId(pos.x, pos.y); }
	
	
	float getBlockSize() const { return this->m_baseBlockSize * this->m_blockScale; }

private:
	Game* m_game;
	
	bool isComplete = false;

	const int m_baseBlockSize = 16;
	float m_blockScale;
	
	sf::Vector2f m_position = sf::Vector2f(0, 0);

	LevelData m_levelData;
	BlocksData m_blocksData;

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

	void loadBackgrounds();


	BlockData getBlockFromId(int id) const
	{
		for (auto block : m_blocksData.blocks)
		{
			if (block.id == id)
				return block;
		}

		std::string message = "Could not find block with id " + std::to_string(id);
		Messager::ShowMessageAndExit(message.c_str());
	}
};

