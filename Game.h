#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Enemy.h"


class World;
class Player;
class IUpdatableObject;
class IDrawableObject;

class Game
{
public:
	Game(sf::RenderWindow& window);
	

	void handleInputs(int deltaTime);
	void update(int deltaTime);
	void draw(int deltaTime);

	World* m_world = nullptr;
	Player* m_player = nullptr;
	Enemy enemies [1];
	
	sf::Vector2u GetScreenSize() const { return m_window.getSize(); }
	
	const float m_blocScale = 2.f;
	float gravityStrength = 0.6f;
private:
	sf::RenderWindow& m_window;
	std::vector<IUpdatableObject*> m_updatableObjects = std::vector<IUpdatableObject*>();
	std::vector<IDrawableObject*> m_drawableObjects = std::vector<IDrawableObject*>();
};

