#include "MenuOver.h"

#include "ButtonMenu.h"

MenuOver::MenuOver(sf::RenderWindow& window, GameState* state): Menu(window, state)
{
	auto* buttonMenu = new ButtonMenu("Back to menu", { static_cast<float>(m_window.getSize().x) / 2.f, static_cast<float>(m_window.getSize().y) / 2.f }, m_font);
	buttonMenu->m_borderColor = sf::Color::White;
	buttonMenu->m_hoveredBorderColor = sf::Color::Blue;
	buttonMenu->m_hoveredTextColor = sf::Color::Blue;
	buttonMenu->m_textColor = sf::Color::White;

	m_buttons.push_back(buttonMenu);

	auto* title = new sf::Text();
	title->setString("GAME OVER");
	title->setFont(*m_font);
	title->setPosition({ static_cast<float>(m_window.getSize().x) / 2.f,200.f });
	title->setCharacterSize(45.f);
	title->setFillColor(sf::Color::Red);
	title->setStyle(sf::Text::Underlined);
	title->setOrigin({ title->getGlobalBounds().width / 2.f, title->getGlobalBounds().height / 2.f });

	m_texts.push_back(title);
}
