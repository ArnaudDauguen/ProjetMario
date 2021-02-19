#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Button.h"
#include "../WindowContext.h"

class Menu
{
protected:
	WindowContext& m_context;
	unsigned int m_selectedButton;
	
public:
	std::vector<Button*> m_buttons;
	std::vector<sf::Text*> m_texts;
	std::shared_ptr<sf::Font> m_font;

	Menu(WindowContext& context);
	~Menu() = default;

	void handleInputs(sf::Event* event);
	void update(int deltaTime);
	void draw(int deltaTime);
};

