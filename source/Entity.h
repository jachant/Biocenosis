//
// Created by Лаба on 27.03.2024.
//

#ifndef BIOCENOSIS_ENTITY_H
#define BIOCENOSIS_ENTITY_H

#include "defines.h"

class Entity {
public:
    sf::RectangleShape shape;
    Entity();
    Entity(const float x, const float y);
    virtual ~Entity(){}

    void render(sf::RenderTarget* target);
};


#endif //BIOCENOSIS_ENTITY_H
