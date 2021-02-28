// C++ standart header files
#include <iostream>
#include <chrono>

// SFML header files
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;
const Color cellColor = Color(255, 0, 0); // Cells color

int getNeigborsCount (Image map, int x, int y)
{
    int count = 0;

    if (map.getPixel(x - 1, y - 1) == cellColor) count++;
    if (map.getPixel(x, y - 1) == cellColor)     count++;
    if (map.getPixel(x + 1, y - 1) == cellColor) count++;

    if (map.getPixel(x - 1, y) == cellColor)     count++;
    if (map.getPixel(x, y) == cellColor)         count++;

    if (map.getPixel(x - 1, y + 1) == cellColor) count++;
    if (map.getPixel(x, y + 1) == cellColor)     count++;
    if (map.getPixel(x + 1, y + 1) == cellColor) count++;

    return count;
}

int main(int argc, char * argv[])
{
    srand (time(NULL));

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game Life");

    // Creating map
    Image map;
    map.create(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Generating cells
    for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT) / 5; i++)
        map.setPixel(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, cellColor);

    // Game Loop
    while (window.isOpen())
    {
        auto tp1 = chrono::system_clock::now();
        auto tp2 = chrono::system_clock::now();

        window.clear();

        for (int i = 1; i < SCREEN_WIDTH - 1; i++)
        {
            for (int j = 1; j < SCREEN_HEIGHT - 1; j++)
            {
                int neigborsN = getNeigborsCount(map, i, j);

                if (neigborsN == 3 && map.getPixel(i, j) == Color::Black) map.setPixel(i, j, cellColor);
                if (neigborsN == 3 || neigborsN == 2) continue;
                if (neigborsN > 3 || neigborsN < 2) map.setPixel(i, j, Color::Black);
            }
        }

        tp2 = chrono::system_clock::now();
        chrono::duration<float> time = tp2 - tp1;
        tp1 = tp2;
        float elaspedTime = time.count();

        cout << "Time elapsed: " << elaspedTime << endl;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        Texture mapTexture;
        mapTexture.loadFromImage(map);

        Sprite mapSprite;
        mapSprite.setTexture(mapTexture);

        window.draw(mapSprite);

        cout << "Drawed!" << endl;
        window.display();
    }

    return 0;
}
