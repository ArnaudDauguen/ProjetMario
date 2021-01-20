#pragma once
#include <SFML/Graphics/RenderWindow.hpp>


class World;
class Player;

class Game
{
public:
	Game(sf::RenderWindow& window);
	

	void handleInputs(int deltaTime);
	void update(int deltaTime);
	void draw(int deltaTime);

	World* world = nullptr;
	Player* player = nullptr;
	
	sf::Vector2u GetScreenSize() const { return m_window.getSize(); }
	
	const int Scale = 2;
private:
	sf::RenderWindow& m_window;
};

