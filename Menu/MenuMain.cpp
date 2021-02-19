#include "MenuMain.h"


#include "ButtonQuit.h"
#include "ButtonStart.h"

MenuMain::MenuMain(WindowContext& context): Menu(context)
{
	auto* buttonStart = new ButtonStart("Start", { static_cast<float>(m_context.window.getSize().x) / 2.f, static_cast<float>(m_context.window.getSize().y) / 2.f }, m_font);
	buttonStart->m_borderColor = sf::Color::White;
	buttonStart->m_hoveredBorderColor = sf::Color::Blue;
	buttonStart->m_hoveredTextColor = sf::Color::Blue;
	buttonStart->m_textColor = sf::Color::White;

	auto* buttonQuit = new ButtonQuit("Quit", { static_cast<float>(m_context.window.getSize().x) / 2.f, static_cast<float>(m_context.window.getSize().y) / 2.f + 200.f }, m_font);
	buttonQuit->m_borderColor = sf::Color::White;
	buttonQuit->m_hoveredBorderColor = sf::Color::Blue;
	buttonQuit->m_hoveredTextColor = sf::Color::Blue;
	buttonQuit->m_textColor = sf::Color::White;

	m_buttons.push_back(buttonStart);
	m_buttons.push_back(buttonQuit);
	
	auto* credits = new sf::Text();
	credits->setString("Arnaud Dauguen, Theo Hay, Justin Sella");
	credits->setFont(*m_font);
	credits->setPosition({ 10.f, 10.f });
	credits->setCharacterSize(12);

	auto* title = new sf::Text();
	title->setFont(*m_font);
	title->setString("Platformer");
	title->setCharacterSize(60);
	title->setStyle(sf::Text::Underlined);
	title->setOrigin({ title->getGlobalBounds().width / 2.f, title->getGlobalBounds().height / 2.f });
	title->setPosition({ static_cast<float>(m_context.window.getSize().x) / 2.f, 150.f });

	m_texts.push_back(title);
	m_texts.push_back(credits);
}
