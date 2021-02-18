#include "ButtonStart.h"

ButtonStart::ButtonStart(const std::string& text, sf::Vector2f position): Button(text, position)
{
}

void ButtonStart::Click(GameState* state)
{
	*state = GameState::GAME;
}
