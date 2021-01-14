#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


// once moved to class, some args will no longer be mandatory
int tryMoveDown(sf::Sprite character, float travelDistancePlanned, int worldPosition, int (&worldMap)[43][23], int worldMapWidth, int worldMapHeigh, float playerSize = 32, float squareOnMapSize = 32) {
    float posX = character.getPosition().x;
    float worldPosY = character.getPosition().y;
    float worldPosX = posX - worldPosition;

    // getting the two down corners
    const std::pair<float, float> firstCornerPosition = { worldPosX,  worldPosY + playerSize }; // bottom left
    const std::pair<float, float> secondCornerPosition = { worldPosX + playerSize, worldPosY + playerSize }; // bottom right

    // convert positions to squares on map
    const std::pair<int, int> firstCornerSquare = { floor(firstCornerPosition.first / squareOnMapSize), floor(firstCornerPosition.second / squareOnMapSize) };
    const std::pair<int, int> secondCornerSquare = { floor(secondCornerPosition.first / squareOnMapSize), floor(secondCornerPosition.second / squareOnMapSize) };
    const bool isAboveOnlyOneBlock = firstCornerSquare.first == secondCornerSquare.first;

    //printf("\nfst point [%d;%d]\n", firstCornerSquare.first, firstCornerSquare.second);
    //printf("scd point [%d;%d]\n", secondCornerSquare.first, secondCornerSquare.second);*/

    //Try moving // direction Down : y++
    bool blocked = false;
    int blockingBlocIndex = 0;
    for (int blocIndexInPath = 0; blocIndexInPath < ceil(travelDistancePlanned / squareOnMapSize); blocIndexInPath++) {
        int blocIndexToTest = firstCornerSquare.second + blocIndexInPath;
        if (blocIndexToTest >= worldMapHeigh || blocIndexToTest < 0 || firstCornerSquare.first >= worldMapWidth || firstCornerSquare.first < 0) { continue; }
        if (worldMap[firstCornerSquare.first][blocIndexToTest] != 0) {
            blocked = true;
            blockingBlocIndex = blocIndexToTest;
        }

        //if above two distinct blocs
        if (!isAboveOnlyOneBlock) {
            if (blocIndexToTest >= worldMapHeigh || blocIndexToTest < 0 || secondCornerSquare.first >= worldMapWidth || secondCornerSquare.first < 0) { continue; }
            if (worldMap[secondCornerSquare.first][blocIndexToTest] != 0) {
                blocked = true;
                blockingBlocIndex = blocIndexToTest;
            }
        }
    }
    float travelDistanceReal = blocked
        ? (blockingBlocIndex * (int)squareOnMapSize) - firstCornerPosition.second //- squareOnMapSize
        : travelDistancePlanned;
    
    return travelDistanceReal;
}


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
    const float PLAYER_SCALE = 1.75;
    const float SPEED = 0.5f;

    const int WORLD_MAP_WIDTH = 43;
    const int WORLD_MAP_HEIGH = 23;

    int POS_W = 640;
    int POS_H = 320;

    int WORLD_W = 0;

    // Create world array
    int world[WORLD_MAP_WIDTH][WORLD_MAP_HEIGH] = { { 0 } };
    for (int i = 0; i < 43; i++) {
        for (int j = 19; j < 21; j++) {
            world[i][j] = 1;
        }
        for (int j = 21; j < WORLD_MAP_HEIGH; j++) {
            world[i][j] = 2;
        }
    }

    sf::Sprite character(stone_texture);

    character.scale(sf::Vector2f(PLAYER_SCALE, PLAYER_SCALE));
    character.setPosition(POS_W, POS_H);
    

    window.setFramerateLimit(144);
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

        //std::cout << elapsed.asMilliseconds() << std::endl;
        
        // "Gravity"
        int falling = tryMoveDown(character, 0.5f * elapsed.asMilliseconds() * SPEED, WORLD_W, world, WORLD_MAP_WIDTH, WORLD_MAP_HEIGH, 16 * PLAYER_SCALE, 16 * SCALE);
        character.move(0.0f, falling);
        
        
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
        

        /*for (int i = 0; i <= 1280 / (16 * SCALE); i++) {
            for (int j = 19; j <= 720 / (16 * SCALE); j++) {
                sf::Sprite dirt_sprite(dirt_texture);

                dirt_sprite.scale(sf::Vector2f(SCALE, SCALE));
                dirt_sprite.setPosition(i * (16 * SCALE) + WORLD_W, j * (16 * SCALE));

                window.draw(dirt_sprite);
            }
        }*/
        for (int i = 0; i < WORLD_MAP_WIDTH; i++) {
            for (int j = 0; j < WORLD_MAP_HEIGH; j++) {
                if (world[i][j] == 0)continue;

                sf::Sprite dirt_sprite(world[i][j] == 1 ? dirt_texture : stone_texture);

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