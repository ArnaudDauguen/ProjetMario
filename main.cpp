#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "World.h"
#include "Actors/Player.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Projet Mario");
    sf::Clock clock;
    Game game(window);
	
    window.setFramerateLimit(144);
	
    while (window.isOpen() /*&& !game.m_world->isLevelComplete() && !game.m_player->isDead()*/)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
    	
        sf::Time elapsed = clock.restart();

        int deltaTime = elapsed.asMilliseconds();

        game.handleInputs(deltaTime, &event);
    	
        game.update(deltaTime);
    	
        game.draw(deltaTime);
    	
        window.display();
    }

    return 0;
}
