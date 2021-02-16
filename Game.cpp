#pragma once

#include "Game.h"

#include <iostream>


#include "Actor.h"
#include "World.h"
#include "Player.h"
#include "SaveReader.h"
#include "Enemies/EGoomba.h"
#include "Enemies/EThwomp.h"

Game::Game(sf::RenderWindow& window) : m_window(window)
{
	auto player = new Player(this, {640, 120}); // world need player
	this->m_world = new World(this, 50, 30, this->m_blocScale);

	this->m_player = std::make_shared<Player>(*player);
	
	this->m_updatableObjects.push_back(this->m_player);
	this->m_drawableObjects.push_back(this->m_player);

	// Spawn Goomba
	sf::Vector2f speeds[] = { {0.15f, 0.f}, {-0.15f, 0.f} };
	for(int i = 0; i < 2; i++)
	{
		auto goomba = new EGoomba(this, {900, 300}, 70, {1.75f, 1.75f}, 0.5f, speeds[i]);
		auto gb = std::make_shared<EGoomba>(*goomba);
		this->m_enemies.push_back(gb);
		this->m_updatableObjects.push_back(gb);
		this->m_drawableObjects.push_back(gb);
	}

	// Spawn Thwomp
	auto thwomp = new EThwomp(this, { 1100, 100 }, 46, {3.75, 5.75});
	auto gb = std::make_shared<EThwomp>(*thwomp);
	this->m_enemies.push_back(gb);
	this->m_updatableObjects.push_back(gb);
	this->m_drawableObjects.push_back(gb);
}

void Game::handleInputs(int deltaTime, sf::Event* event)
{
	this->m_player->handleInputs(deltaTime, event);
}

void Game::update(int deltaTime)
{
	m_updatableObjects.erase(std::remove_if(m_updatableObjects.begin(), m_updatableObjects.end(), [](std::shared_ptr<IUpdatableObject> ele)->bool
		{
			return ele->mustDie();
		}), m_updatableObjects.end());
	m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), [](std::shared_ptr<Actor> ele)->bool
		{
			return ele->mustDie();
		}), m_enemies.end());

	for (const auto& obj : m_updatableObjects)
	{
		obj->update(deltaTime);
	}
	
	/*for (const auto& enemy : this->m_enemies)
	{
		enemy->update(deltaTime);
	}*/
}

void Game::draw(int deltaTime)
{
	this->m_world->draw(this->m_window);
	
	m_drawableObjects.erase(std::remove_if(m_drawableObjects.begin(), m_drawableObjects.end(), [](std::shared_ptr<IDrawableObject> ele)->bool
		{
			return ele->mustDie();
		}), m_drawableObjects.end());

	for (const auto& obj : m_drawableObjects)
	{
		obj->draw(this->m_window);
	}

	/*for (const auto& enemy : this->m_enemies)
	{
		enemy->draw(this->m_window);
	}*/
}

