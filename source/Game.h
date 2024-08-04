#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "defines.h"
#include "Grass.h"
#include "Grasseaters.h"
#include "Hunter.h"
#include "Rain.h"
#include "Particles.h"

class Game
{
private:
    int timeCount = 0;

    sf::RectangleShape background;
    sf::Texture backgroundTexture;

    sf::RenderWindow *window;
    sf::Event sfEvent;

    long grassCounter = 0;

    void initWindow();
    void initBackground();
public:
    Game();
    ~Game();

    void updateSFMLEvents();
    void update();
    void render();
    void run();

    static  sf::Clock dtClock;
    static float dt;
    static void updatedt();
};
#endif