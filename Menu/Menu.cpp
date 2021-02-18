#include "Menu.h"

Menu::Menu(sf::RenderWindow& window, GameState* state): m_gameState(state), m_window(window), m_selectedButton(0)
{
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
}
