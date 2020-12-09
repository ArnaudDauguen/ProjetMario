#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    const int SCREEN_W = 1280;
    const int SCREEN_H = 720;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    sf::Texture dirt_texture;
    if (!dirt_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 2, 0 + 16 * 0, 16, 16)))
        return EXIT_FAILURE;
    
    sf::Texture stone_texture;
    if (!stone_texture.loadFromFile("Textures/terrain.png", sf::IntRect(0 + 16 * 0, 0 + 16 * 0, 16, 16)))
        return EXIT_FAILURE;

    const int SCALE = 2;
    const float SPEED = 0.5f;

    int POS_W = 0;
    int POS_H = 576;

    int WORLD_W = 0;

    sf::Sprite character(stone_texture);

    character.scale(sf::Vector2f(SCALE, SCALE));
    character.setPosition(POS_W, POS_H);
    

    window.setFramerateLimit(240);
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::Time elapsed = clock.restart();

        std::cout << elapsed.asMilliseconds() << std::endl;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            character.move(-1.f * elapsed.asMilliseconds() * SPEED, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            character.move(1.f * elapsed.asMilliseconds() * SPEED, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            character.move(0.0f, -1.0f * elapsed.asMilliseconds() * SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            character.move(0.0f, 1.0f * elapsed.asMilliseconds() * SPEED);
        }
        
        auto pos = character.getPosition();

        if (pos.x > (SCREEN_W * 3 / 4)) {
            character.setPosition(SCREEN_W * 3 / 4, pos.y);
            WORLD_W--;
        }

        if (pos.x < (SCREEN_W * 1 / 4)) {
            character.setPosition(SCREEN_W * 1 / 4, pos.y);
            WORLD_W++;
        }
        

        for (int i = 0; i <= 1280 / (16 * SCALE); i++) {
            for (int j = 19; j <= 720 / (16 * SCALE); j++) {
                sf::Sprite dirt_sprite(dirt_texture);

                dirt_sprite.scale(sf::Vector2f(SCALE, SCALE));
                dirt_sprite.setPosition(i * (16 * SCALE) + WORLD_W, j * (16 * SCALE));

                window.draw(dirt_sprite);
            }
        }

        window.draw(character);
        
        window.display();
    }

    return 0;
}