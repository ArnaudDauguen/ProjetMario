#include "ButtonStart.h"

ButtonStart::ButtonStart(const std::string& text, sf::Vector2f position, std::shared_ptr<sf::Font> font): Button(text, position, std::move(font))
{
}

void ButtonStart::Click(GameState* state)
{
	*state = GameState::GAME;
}
