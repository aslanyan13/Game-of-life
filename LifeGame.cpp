// C++ standart header files
#include <iostream>
#include <chrono>
#include <windows.h>
#include <time.h>
#include <cstdlib>

// SFML header files
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Screen size constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

// Map size constants
const int MAP_WIDTH = 1200;
const int MAP_HEIGHT = 1200;

int getNeigborsCount (bool map[MAP_HEIGHT][MAP_WIDTH], int x, int y)
{
    int count = 0;

    if (map[y - 1][x - 1]) count++;
    if (map[y - 1][x]) count++;
    if (map[y - 1][x + 1]) count++;

    if (map[y][x - 1]) count++;
    if (map[y][x + 1]) count++;

    if (map[y + 1][x - 1]) count++;
    if (map[y + 1][x]) count++;
    if (map[y + 1][x + 1]) count++;

    return count;
}

int main(int argc, char * argv[])
{
    srand (time(NULL));

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game Life");

    View camera(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    // Creating map
    Image mapImg;
    mapImg.create(MAP_WIDTH, MAP_HEIGHT);

    bool map[MAP_HEIGHT][MAP_WIDTH];

    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
            map[i][j] = false;

    // Generating cells
    for (int i = 0; i < (MAP_WIDTH * MAP_HEIGHT) / 20; i++)
        map[rand() % MAP_HEIGHT][rand() % MAP_WIDTH] = true;

    camera.zoom(1);

    float cameraX = 0, cameraY = 0;

    // Game Loop
    while (window.isOpen())
    {
        window.clear();
        window.setView(camera);

        // Camera Zoom-In
        if (Keyboard::isKeyPressed(Keyboard::Add))
        {
            camera.zoom(0.9);
        }
        // Camera Zoom-Out
        if (Keyboard::isKeyPressed(Keyboard::Subtract))
        {
            camera.zoom(1.1);
        }

        // Camera Moving
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            cameraY-=10;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            cameraY+=10;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            cameraX-=10;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            cameraX+=10;
        }

        if (cameraX < 0) cameraX = 0;
        if (cameraY < 0) cameraY = 0;

        if (cameraX > SCREEN_WIDTH) cameraX = SCREEN_WIDTH;
        if (cameraY > SCREEN_HEIGHT) cameraY = SCREEN_HEIGHT;

        camera.setCenter(SCREEN_WIDTH / 2 + cameraX, SCREEN_HEIGHT / 2 + cameraY);

        for (int i = 1; i < MAP_HEIGHT - 1; i++)
        {
            for (int j = 1; j < MAP_WIDTH - 1; j++)
            {
                int neigborsN = getNeigborsCount(map, j, i);

                if (neigborsN == 3 && !map[i][j]) {
                    map[i][j] = true;
                    // mapImg.setPixel(j, i, Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
                    mapImg.setPixel(j, i, Color::Red);
                }
                if (neigborsN == 3 || neigborsN == 2) continue;
                if (neigborsN > 3 || neigborsN < 2) {
                    map[i][j] = false;
                    mapImg.setPixel(j, i, Color::Black);
                }
            }
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        Texture mapTexture;
        mapTexture.loadFromImage(mapImg);

        Sprite mapSprite;
        mapSprite.setPosition(0, 0);
        mapSprite.setTexture(mapTexture);

        window.draw(mapSprite);
        window.display();
    }

    return 0;
}
