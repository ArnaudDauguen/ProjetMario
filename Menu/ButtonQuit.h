#pragma once
#include "Button.h"

class ButtonQuit : public Button
{
public:
	ButtonQuit(const std::string& text, sf::Vector2f position, std::shared_ptr<sf::Font> font);
	
	void Click(WindowContext& context) override;
};

