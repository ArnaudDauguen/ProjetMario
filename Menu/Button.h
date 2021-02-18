#pragma once
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../GameState.h"

class Button
{
private:
	sf::RectangleShape m_box;
	sf::Text m_text;
	bool m_hovered = false;

public:
	sf::Color m_borderColor;
	sf::Color m_hoveredBorderColor;
	sf::Color m_backgroundColor;
	sf::Color m_hoveredBackgroundColor;
	sf::Color m_textColor;
	sf::Color m_hoveredTextColor;
	sf::Font m_textFont;
	
	Button() = default;
	Button(const std::string& text, sf::Vector2f position);
	virtual ~Button() = default;

	virtual void Click(GameState* state) = 0;
	void SetHovered(const bool hovered);

	sf::RectangleShape GetBox() const { return m_box; }
	sf::Text GetText() const { return m_text; }
};

