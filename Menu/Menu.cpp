#include "Menu.h"

Menu::Menu(sf::RenderWindow& window, GameState* state): m_gameState(state), m_window(window), m_selectedButton(0), m_font(std::make_shared<sf::Font>(sf::Font()))
{
	if (!m_font->loadFromFile("Textures/PIXEAB__.TTF"))
		std::cout << "cannot load font" << std::endl;
}

void Menu::handleInputs(sf::Event* event)
{	
	if (event->type == sf::Event::KeyReleased) {
		switch (event->key.code)
		{
		case sf::Keyboard::Up:
			this->m_selectedButton = this->m_selectedButton + 1 == m_buttons.size() ? 0 : this->m_selectedButton + 1;
			break;
		case sf::Keyboard::Down:
			this->m_selectedButton = static_cast<short>(this->m_selectedButton) - 1 < 0 ? m_buttons.size() - 1 : this->m_selectedButton - 1;
			break;
		case sf::Keyboard::Enter:
		case sf::Keyboard::Space:
			m_buttons.at(m_selectedButton)->Click(m_gameState);
			break;
		default:
			break;
		}
	}

	if (event->type == sf::Event::MouseMoved)
	{
		for (unsigned int i = 0; i < m_buttons.size(); ++i)
		{
			if (m_buttons[i]->GetBox().getGlobalBounds().contains({ static_cast<float>((*event).mouseMove.x), static_cast<float>((*event).mouseMove.y) }))
				m_selectedButton = i;
		}
	}

	if (event->type == sf::Event::MouseButtonPressed)
	{
		const auto mousePosition = sf::Mouse::getPosition(m_window);

		switch (event->mouseButton.button)
		{
		case sf::Mouse::Left:
			if (m_buttons[m_selectedButton]->GetBox().getGlobalBounds().contains({ static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) }))
				m_buttons.at(m_selectedButton)->Click(m_gameState);
			break;
		default:
			break;
		}
	}
}

void Menu::update(int deltaTime)
{
	for (unsigned int i = 0; i < m_buttons.size(); ++i) 
	{
		m_buttons[i]->SetHovered(i == m_selectedButton);
	}
}

void Menu::draw(int deltaTime)
{
	for (const auto& button : m_buttons)
	{
		m_window.draw(button->GetBox());
		m_window.draw(button->GetText());
	}

	for (const auto& text : m_texts)
	{
		m_window.draw(*text);
	}
}
