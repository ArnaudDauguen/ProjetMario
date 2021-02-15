#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class World;
class Player;
class IUpdatableObject;
class IDrawableObject;
class Enemy;

class Game
{
public:
	Game(sf::RenderWindow& window);
	

	void handleInputs(int deltaTime, sf::Event* event);
	void update(int deltaTime);
	void draw(int deltaTime);

	World* m_world = nullptr;
	std::shared_ptr<Player> m_player = nullptr;
	std::vector<std::shared_ptr<Enemy>> m_enemies = std::vector<std::shared_ptr<Enemy>>();
	
	sf::Vector2u GetScreenSize() const { return m_window.getSize(); }
	
	const float m_blocScale = 2.f;
	float m_gravityStrength = 0.6f;
private:
	sf::RenderWindow& m_window;
	std::vector<std::shared_ptr<IUpdatableObject>> m_updatableObjects = std::vector<std::shared_ptr<IUpdatableObject>>();
	std::vector<std::shared_ptr<IDrawableObject>> m_drawableObjects = std::vector<std::shared_ptr<IDrawableObject>>();
};

