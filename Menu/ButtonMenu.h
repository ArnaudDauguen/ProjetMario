#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics/Font.hpp>

#include "Button.h"

class ButtonMenu : public Button
{
public:
	ButtonMenu(const std::string& text, sf::Vector2f position, std::shared_ptr<sf::Font> font);

	void Click(WindowContext& context) override;
};

