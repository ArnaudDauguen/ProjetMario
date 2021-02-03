#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "IDrawableObject.h"
#include "IUpdatableObject.h"

namespace sf {
	class RenderWindow;
}

class Game;

class Player : public IDrawableObject, public IUpdatableObject
{
public:
	Player(Game* game, int x, int y, float scale);

	void handleInputs(int deltaTime);
	
	void update(int deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	bool mustDie() override { return false; }
private:
	Game* m_game;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	
	float m_speed = 0.5f;

	float TryMoveDown(float distance);


	
	sf::Vector2f GetCharacterSize() const {
		return {
		m_sprite.getTexture()->getSize().x * m_sprite.getScale().x,
		m_sprite.getTexture()->getSize().y * m_sprite.getScale().y
		};
	}
};

