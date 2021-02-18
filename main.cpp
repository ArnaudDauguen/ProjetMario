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
    Game game(window);
    auto gameState = GameState::MENU;
    MenuMain menu(window, &gameState);
	
	
    while (window.isOpen() && !game.m_world->isLevelComplete() && !game.m_player->isDead())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            menu.handleInputs(&event);
        	//player jump
            /*if (event.type == sf::Event::KeyReleased)
                if (event.key.code == sf::Keyboard::Up)
                    game.m_player->jump();*/
        }

        window.clear();
    	
        sf::Time elapsed = clock.restart();

        int deltaTime = elapsed.asMilliseconds();

        switch (gameState)
        {
	        case GameState::GAME:
	            game.handleInputs(deltaTime, &event);
	            game.update(deltaTime);
	            game.draw(deltaTime);
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
