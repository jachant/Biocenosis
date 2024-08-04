//
// Created by Андрей Степанов on 02.04.2024.
//

#include "Particles.h"

Particles::Particles(const float x, const float y) : Entity(x, y) {
    clock = 0;
    rectSourceSprite = sf::IntRect(0, 0, 16, 16);
    sprite = sf::Sprite(texture, rectSourceSprite);
    sprite.setScale(5, 5);
    sprite.setPosition(x, y);
}



bool Particles::renderParticles(sf::RenderTarget *target) {
    if (++clock > 2) {
        if (rectSourceSprite.left >= 112){
            delete this;
            return false;
        }
        else {
            rectSourceSprite.left += 16;
        }
        sprite.setTextureRect(rectSourceSprite);
        clock = 0;
    }
    target->draw(sprite);
    return true;
}

void Particles::renderVector(sf::RenderTarget *target) {
    int len = particles.size();
    len -= (len > 1) ? 1 : 0;
    int i = 0;
    for (; i < len; i++) {
        if (!particles[i]->renderParticles(target)){
            i = 0;
        }
    }
}

Particles::~Particles() {
    const int len = Particles::particles.size();
    int i;
    for (i = 0; i < len; i++) {
        if (Particles::particles[i] == this) {
            break;
        }
    }
    Particles::particles.erase(Particles::particles.begin() + i);
}

void Particles::initParticles() {
    texture.loadFromFile("textures/death.png");

}

sf::Texture Particles::texture;
std::vector<Particles*> Particles::particles;