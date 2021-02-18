#pragma once

#include "Game.h"

#include <iostream>


#include "Actor.h"
#include "World.h"
#include "SaveReader.h"
#include "Actors/Player.h"
#include "Actors/EGoomba.h"
#include "Actors/EThwomp.h"

Game::Game(sf::RenderWindow& window) : m_window(window)
{
	this->m_screen = sf::FloatRect(
		{ 0.f,0.f },
		{ (float)window.getSize().x, (float)window.getSize().y }
	);
	
	this->loadAllTextures();

	Player* player = nullptr;
	
	auto actors = SaveReader::GetActorsData();
	for (const auto& actor : actors.actors)
	{
		switch (actor.type)
		{
		case 0:
			{
				player = new Player(this, { actor.spawnX, actor.spawnY });
				
				this->m_world = new World(this, this->m_blocScale);
				
				this->m_player = std::make_shared<Player>(*player);
				
				this->m_updatableObjects.push_back(this->m_player);
				this->m_drawableObjects.push_back(this->m_player);
				
				break;
			}
		case 1:
			{
				const auto goomba = new EGoomba(this, { actor.spawnX, actor.spawnY }, actor.textureLocationId, { 1.75f, 1.75f });
				auto gb = std::make_shared<EGoomba>(*goomba);
				this->m_enemies.push_back(gb);
				this->m_updatableObjects.push_back(gb);
				this->m_drawableObjects.push_back(gb);
				break;
			}
		case 2:
			{
				const auto thwomp = new EThwomp(this, { actor.spawnX, actor.spawnY }, actor.textureLocationId, { 3.75, 5.75 });
				auto gb = std::make_shared<EThwomp>(*thwomp);
				this->m_enemies.push_back(gb);
				this->m_updatableObjects.push_back(gb);
				this->m_drawableObjects.push_back(gb);
				break;
			}
		}
	}

	if (player == nullptr)
	{
		Messager::ShowMessageAndExit("You have to declare a player in file actors.json.");
		return;
	}
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
}

void Game::loadAllTextures()
{
	sf::Image terainPNG;
	terainPNG.loadFromFile("Textures/terrain.png");
	terainPNG.createMaskFromColor(sf::Color(255, 255, 255)); // Treat White as transparent
	terainPNG.createMaskFromColor(sf::Color(214, 127, 255)); // Treat Purple as transparent
	
	for (int y = 0; y < this->m_yTextureLength; ++y)
	{
		for (int x = 0; x < this->m_xTextureLength; ++x)
		{
			if (!this->m_blockTextures[y * this->m_yTextureLength + x].loadFromImage(terainPNG, sf::IntRect(m_textureSizeOnImage * x, m_textureSizeOnImage * y, 16, 16)))
				std::cout << "Issue with loading the m_world texture " << y * 16 + x << std::endl;
		}
	}
}


