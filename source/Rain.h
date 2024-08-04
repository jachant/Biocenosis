//
// Created by 1ghaw on 28.03.2024.
//

#ifndef BIOCENOSIS_RAIN_H
#define BIOCENOSIS_RAIN_H
#include "defines.h"

class Rain {
public:
    Rain(float x, float y);
    ~Rain();

    bool checkState();

    static void initRain();
    static void renderVector(sf::RenderTarget* target);
    static std::vector<Rain*> rain;
private:
    void render(sf::RenderTarget* target);
    sf::RectangleShape shape;
    sf::Texture texture;
    void updateRain();
    int timer;
    int raintime;
    int rainstart;
};


#endif //BIOCENOSIS_RAIN_H
