#include "ButtonQuit.h"

ButtonQuit::ButtonQuit(const std::string& text, sf::Vector2f position): Button(text, position)
{
}

void ButtonQuit::Click(GameState* state)
{
	*state = GameState::QUIT;
}
