#pragma once
#include "Button.h"

class ButtonStart : public Button
{
public:
	ButtonStart(const std::string& text, sf::Vector2f position);
	
	void Click(GameState* state) override;
};
