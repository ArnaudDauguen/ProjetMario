#pragma once

#include "Game.h"

#include <iostream>


#include "Actor.h"
#include "World.h"
#include "Player.h"
#include "SaveReader.h"
#include "Enemy.h"
#include "Enemies/EGoomba.h"

Game::Game(sf::RenderWindow& window) : m_window(window)
{
	this->m_player = new Player(this, 640, 120, 1.75f, 1); // world need player
	this->m_world = new World(this, 50, 30, this->m_blocScale);
	
	
	this->m_updatableObjects.push_back(this->m_player);
	this->m_drawableObjects.push_back(this->m_world);
	this->m_drawableObjects.push_back(this->m_player);
	

	auto goomba = new EGoomba(this, 1500, 120, 1.75f, 1, 1);

	this->enemies.push_back(std::make_shared<EGoomba>(*goomba));
}

void Game::handleInputs(int deltaTime)
{
	this->m_player->handleInputs(deltaTime);
}

void Game::update(int deltaTime)
{
	std::cout << this->enemies[0]->GetLocationX() << std::endl;
	m_updatableObjects.erase(std::remove_if(m_updatableObjects.begin(), m_updatableObjects.end(), [](IUpdatableObject* ele)->bool
		{
			return ele->mustDie();
		}), m_updatableObjects.end());

	for (auto* obj : m_updatableObjects)
	{
		obj->update(deltaTime);
	}
	
	for (const auto& enemy : this->enemies)
	{
		enemy->update(deltaTime);
	}
}

void Game::draw(int deltaTime)
{	
	m_drawableObjects.erase(std::remove_if(m_drawableObjects.begin(), m_drawableObjects.end(), [](IDrawableObject* ele)->bool
		{
			return ele->mustDie();
		}), m_drawableObjects.end());

	for (auto* obj : m_drawableObjects)
	{
		obj->draw(this->m_window);
	}

	for (const auto& enemy : this->enemies)
	{
		enemy->draw(this->m_window);
	}
}

