//
// Created by 1ghaw on 28.03.2024.
//

#ifndef BIOCENOSIS_GRASS_H
#define BIOCENOSIS_GRASS_H
#include "Entity.h"

class Grass: public Entity {
    static sf::Texture texture;
public:
    Grass();
    ~Grass();

    static void initGrass();
    static std::vector<Grass*> grass;
    static void renderVector(sf::RenderTarget* target);
};


#endif //BIOCENOSIS_GRASS_H
