#include "Game.h"

#include "World.h"
#include "Player.h"

Game::Game(sf::RenderWindow& window) : m_window(window)
{
	this->world = new World(this, 43, 23);
	this->player = new Player(this, 640, 320, 1.75f);
}

void Game::handleInputs(int deltaTime)
{
	this->player->handleInputs(deltaTime);
}

void Game::update(int deltaTime)
{
	this->player->update(deltaTime);
}

void Game::draw(int deltaTime)
{
	this->player->draw(this->m_window);

	this->world->draw(this->m_window);
}

