#include "ButtonQuit.h"

ButtonQuit::ButtonQuit(const std::string& text, sf::Vector2f position): Button(text, position)
{
}

void ButtonQuit::Click(GameState* state)
{
	std::cout << "test" << std::endl;
	*state = GameState::QUIT;
}
