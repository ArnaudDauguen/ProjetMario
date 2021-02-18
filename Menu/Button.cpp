#include "Button.h"

#include <utility>

Button::Button(const std::string& text, sf::Vector2f position, std::shared_ptr<sf::Font> font): m_hovered(false), m_textFont(std::move(font))
{
	m_text.setFont(*m_textFont);
	m_text.setOutlineThickness(10.f);
	m_text.setString(text);
	m_text.setFillColor(m_textColor);
	m_text.setCharacterSize(35.f);
	m_text.setOrigin({ m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height / 2.f });
	m_text.setPosition(position);

	m_box.setFillColor(m_backgroundColor);
	m_box.setSize({ m_text.getGlobalBounds().width + 100.f, m_text.getGlobalBounds().height + 25.f });
	m_box.setOrigin({ m_box.getSize().x / 2, m_box.getSize().y / 2 });
	m_box.setPosition(m_text.getPosition());
}


void Button::SetHovered(const bool hovered)
{
	m_hovered = hovered;

	m_box.setFillColor(m_hovered ? m_hoveredBackgroundColor : m_backgroundColor);
	m_box.setOutlineColor(m_hovered ? m_hoveredBorderColor : m_borderColor);
	m_text.setFillColor(m_hovered ? m_hoveredTextColor : m_textColor);
}
