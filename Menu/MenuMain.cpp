#include "MenuMain.h"


#include "ButtonQuit.h"
#include "ButtonStart.h"

MenuMain::MenuMain(sf::RenderWindow& window, GameState* state): Menu(window, state)
{
	auto* buttonStart = new ButtonStart("Start", { static_cast<float>(m_window.getSize().x) / 2.f, static_cast<float>(m_window.getSize().y) / 2.f });
	buttonStart->m_borderColor = sf::Color::White;
	buttonStart->m_hoveredBorderColor = sf::Color::Blue;
	buttonStart->m_hoveredTextColor = sf::Color::Blue;
	buttonStart->m_textColor = sf::Color::White;

	auto* buttonQuit = new ButtonQuit("Quit", { static_cast<float>(m_window.getSize().x) / 2.f, static_cast<float>(m_window.getSize().y) / 2.f + 200.f });
	buttonQuit->m_borderColor = sf::Color::White;
	buttonQuit->m_hoveredBorderColor = sf::Color::Blue;
	buttonQuit->m_hoveredTextColor = sf::Color::Blue;
	buttonQuit->m_textColor = sf::Color::White;

	m_buttons.push_back(buttonStart);
	m_buttons.push_back(buttonQuit);
}
