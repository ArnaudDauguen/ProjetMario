#include "ButtonMenu.h"


ButtonMenu::ButtonMenu(const std::string& text, sf::Vector2f position, std::shared_ptr<sf::Font> font) : Button(text, position, std::move(font))
{
}

void ButtonMenu::Click(WindowContext& context)
{
	context.state = GameState::MENU;
}
