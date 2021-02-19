#pragma once
#include "Button.h"

class ButtonStart : public Button
{
public:
	ButtonStart(const std::string& text, sf::Vector2f position, std::shared_ptr<sf::Font> font);
	
	void Click(WindowContext& context) override;
};
