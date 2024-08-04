//
// Created by Андрей Степанов on 02.04.2024.
//

#ifndef BIOCENOSIS_PARTICLES_H
#define BIOCENOSIS_PARTICLES_H

#include "Entity.h"

class Particles: Entity {
private:
    static sf::Texture texture;
    sf::IntRect rectSourceSprite;
    sf::Sprite sprite;
    int clock;
public:
    Particles(const float x, const float y);
    ~Particles();
    static std::vector<Particles*> particles;
    static void initParticles();

    bool renderParticles(sf::RenderTarget *target);
    static void renderVector(sf::RenderTarget *target);
};


#endif //BIOCENOSIS_PARTICLES_H
