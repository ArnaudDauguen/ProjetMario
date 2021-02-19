#include "MenuOver.h"

#include "ButtonMenu.h"

MenuOver::MenuOver(WindowContext& context): Menu(context)
{
	auto* buttonMenu = new ButtonMenu("Back to menu", { static_cast<float>(m_context.window.getSize().x) / 2.f, static_cast<float>(m_context.window.getSize().y) / 2.f }, m_font);
	buttonMenu->m_borderColor = sf::Color::White;
	buttonMenu->m_hoveredBorderColor = sf::Color::Blue;
	buttonMenu->m_hoveredTextColor = sf::Color::Blue;
	buttonMenu->m_textColor = sf::Color::White;

	m_buttons.push_back(buttonMenu);

	auto* title = new sf::Text();
	title->setString("GAME OVER");
	title->setFont(*m_font);
	title->setPosition({ static_cast<float>(m_context.window.getSize().x) / 2.f,200.f });
	title->setCharacterSize(45);
	title->setFillColor(sf::Color::Red);
	title->setStyle(sf::Text::Underlined);
	title->setOrigin({ static_cast<float>(title->getGlobalBounds().width) / 2.f, static_cast<float>(title->getGlobalBounds().height) / 2.f });

	m_texts.push_back(title);
}
