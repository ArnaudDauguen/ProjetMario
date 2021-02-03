#include "Game.h"

#include "World.h"
#include "Player.h"

Game::Game(sf::RenderWindow& window) : m_window(window)
{
	this->m_world = new World(this, 43, 23);
	this->m_player = new Player(this, 640, 120, 1.75f);

	this->m_updatableObjects.push_back(this->m_player);
	this->m_drawableObjects.push_back(this->m_world);
	this->m_drawableObjects.push_back(this->m_player);
	
}

void Game::handleInputs(int deltaTime)
{
	this->m_player->handleInputs(deltaTime);
}

void Game::update(int deltaTime)
{
	m_updatableObjects.erase(std::remove_if(m_updatableObjects.begin(), m_updatableObjects.end(), [](IUpdatableObject* ele)->bool
		{
			return ele->mustDie();
		}), m_updatableObjects.end());

	for (auto* obj : m_updatableObjects)
	{
		obj->update(deltaTime);
	}
}

void Game::draw(int deltaTime)
{	
	m_drawableObjects.erase(std::remove_if(m_drawableObjects.begin(), m_drawableObjects.end(), [](IDrawableObject* ele)->bool
		{
			return ele->mustDie();
		}), m_drawableObjects.end());

	for (auto& obj : m_drawableObjects)
	{
		obj->draw(this->m_window);
	}
}
