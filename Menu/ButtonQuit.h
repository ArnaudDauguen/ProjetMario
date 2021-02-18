#pragma once
#include "Button.h"

class ButtonQuit : public Button
{
public:
	ButtonQuit(const std::string& text, sf::Vector2f position);
	
	void Click(GameState * state) override;
};

