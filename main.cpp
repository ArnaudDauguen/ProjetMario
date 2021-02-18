#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "GameState.h"
#include "Menu/MenuMain.h"
#include "World.h"
#include "Actors/Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Projet Mario");
    sf::Clock clock;
    auto* game = new Game(window);
    auto gameState = GameState::MENU;
    MenuMain menu(window, &gameState);

    window.setFramerateLimit(144);
	
    while (window.isOpen())
    {
        if (game->m_world->isLevelComplete() || game->m_player->isDead()) {
            gameState = GameState::MENU;
            delete game;
            game = new Game(window);
        }
    	
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameState == GameState::GAME)
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    gameState = GameState::MENU;
                    delete game;
                    game = new Game(window);
                }

            if (gameState == GameState::MENU)
                menu.handleInputs(&event);
        }

        window.clear();
    	
        sf::Time elapsed = clock.restart();

        int deltaTime = elapsed.asMilliseconds();

        switch (gameState)
        {
	        case GameState::GAME:
	            game->handleInputs(deltaTime, &event);
	            game->update(deltaTime);
	            game->draw(deltaTime);
	            break;
	        case GameState::MENU:
	            menu.update(deltaTime);
	            menu.draw(deltaTime);
	            break;
            case GameState::QUIT:
                return 0;
        }
    	
        window.display();
    }

    return 0;
}
