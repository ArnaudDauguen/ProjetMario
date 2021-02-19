#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

class World;
class Player;
class Actor;
class Enemy;

const int xTextureLength = 16;
const int yTextureLength = 16;
const int blockTextureLength = xTextureLength * yTextureLength;
const int textureSizeOnImage = 16;

class Game
{
public:
	Game(sf::RenderWindow& window);
	// ~Game();

	void handleInputs(int deltaTime, sf::Event* event);
	void update(int deltaTime);
	void draw(int deltaTime);

	World* m_world = nullptr;
	std::shared_ptr<Player> m_player = nullptr;
	std::vector<std::shared_ptr<Actor>> m_enemies = std::vector<std::shared_ptr<Actor>>();

	void killActor(Actor* actorToDrop);
	
	sf::Vector2u GetScreenSize() const { return m_window.getSize(); }
	
	sf::Texture* getTexture(int textureIndex) { return textureIndex < this->m_blockTextureLength ? &this->m_blockTextures[textureIndex] : nullptr; }
	
	const float m_blocScale = 2.f;
	float m_gravityStrength = 0.6f;
	sf::FloatRect m_screen;
private:
	sf::RenderWindow& m_window;
	std::vector<std::shared_ptr<Actor>> m_actors = std::vector<std::shared_ptr<Actor>>();

	const int m_xTextureLength = xTextureLength;
	const int m_yTextureLength = yTextureLength;
	const int m_blockTextureLength = blockTextureLength;
	sf::Texture m_blockTextures[blockTextureLength];
	const int m_textureSizeOnImage = textureSizeOnImage;

	void loadAllTextures();


	std::vector<std::shared_ptr<Actor>>::iterator contains(Actor* block) {
		return std::find_if(m_actors.begin(), m_actors.end(), [block](std::shared_ptr<Actor> const& i) {
			return i.get() == block;
		});
	}

	void cleanupActors();
};

