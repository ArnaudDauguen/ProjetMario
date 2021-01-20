#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace sf {
	class RenderWindow;
}

class Game;

class Player
{
public:
	Player(Game* game, int x, int y, float scale);

	void handleInputs(int deltaTime);
	
	void update(int deltaTime);
	void draw(sf::RenderWindow& window) const;
private:
	Game* m_game;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	
	float m_speed = 0.5f;

	int TryMoveDown(float distance);


	
	sf::Vector2f GetCharacterSize() const {
		return {
		m_sprite.getTexture()->getSize().x * m_sprite.getScale().x,
		m_sprite.getTexture()->getSize().y * m_sprite.getScale().y
		};
	}
};

