#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Game.h"
#include "GameState.h"

struct WindowContext
{
	sf::RenderWindow& window;
	Game& game;
	GameState& state;
};
