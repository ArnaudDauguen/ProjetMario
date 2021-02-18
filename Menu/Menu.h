#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Button.h"

class Menu
{
protected:
	GameState* m_gameState;
	sf::RenderWindow& m_window;
	unsigned int m_selectedButton;
	
public:
	std::vector<Button*> m_buttons;

	Menu(sf::RenderWindow& window, GameState* state);
	~Menu() = default;

	void handleInputs(sf::Event* event);
	void update(int deltaTime);
	void draw(int deltaTime);
};

