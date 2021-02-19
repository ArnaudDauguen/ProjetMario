#include "ButtonQuit.h"

ButtonQuit::ButtonQuit(const std::string& text, sf::Vector2f position, std::shared_ptr<sf::Font> font): Button(text, position, std::move(font))
{
}

void ButtonQuit::Click(WindowContext& context)
{
	context.state = GameState::QUIT;
}
