#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class IDrawableObject
{
public:
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual bool mustDie() = 0;
	virtual ~IDrawableObject() = default;
};
