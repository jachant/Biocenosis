//
// Created by 1ghaw on 28.03.2024.
//

#include "Grass.h"
#include <iostream>

Grass::Grass() : Entity() {
    sf::Vector2f pos(rand() % 17 * SPRITE_SIZE, rand() % 17 * SPRITE_SIZE);
    const int grassCount = grass.size();
    if (grassCount < 289) {
        int i = 0;
        for (; i < grassCount; i++) {
            if (pos == grass[i]->shape.getPosition()) {
                i = 0;
                pos = sf::Vector2f(rand() % 17 * SPRITE_SIZE, rand() % 17 * SPRITE_SIZE);
            }
        }
        this->shape.setPosition(pos);
        this->shape.setSize(sf::Vector2f(SPRITE_SIZE, SPRITE_SIZE));
        this->shape.setTexture(&texture);
    }
}

void Grass::renderVector(sf::RenderTarget *target) {
    for (auto &grasses: grass) {
        grasses->render(target);
    }
}

Grass::~Grass() {
    const int len = Grass::grass.size();
    int i;
    for (i = 0; i < len; i++) {
        if (Grass::grass[i] == this) {
            break;
        }
    }
    Grass::grass.erase(Grass::grass.begin() + i);
}

void Grass::initGrass() {
    Grass::texture.loadFromFile("textures/grass.png");
    for (int i = 0; i < GRASS_START; i++)
        Grass::grass.push_back(new Grass());
}

sf::Texture Grass::texture;
std::vector<Grass *> Grass::grass;