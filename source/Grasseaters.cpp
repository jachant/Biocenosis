//
// Created by Андрей Степанов on 28.03.2024.
//

#include "Grasseaters.h"
#include <iostream>

void Grasseaters::foo(){
    name = "grasseater";
    speed = GRASSEATERS_MOVEMENT_SPEED;
    deathLimit = GRASSEATERS_LIFE_TIME;
    hungerLimit = GRASSEATERS_HUNGER_DEATH;
    sexGate = GRASSEATERS_SEX;
    hungerGate = GRASSEATERS_HUNGER;
    this->shape.setTexture(&texture);
}

Grasseaters::Grasseaters() : Alives() {
    foo();
}

Grasseaters::Grasseaters(const float x, const float y) : Alives(x, y) {
    foo();
}

void Grasseaters::findFood() {
    float localMin = 100000;
    Grass *newHusband;
    bool check = false;
    for (auto &gras: Grass::grass) {
        float distance = sqrt((this->shape.getPosition().x - gras->shape.getPosition().x) *
                              (this->shape.getPosition().x - gras->shape.getPosition().x) +
                              (this->shape.getPosition().y - gras->shape.getPosition().y) *
                              (this->shape.getPosition().y - gras->shape.getPosition().y));
        if (distance < localMin) {
            check = true;
            localMin = distance;
            newHusband = gras;
        }
    }
    if (check) {
        this->destination.x = newHusband->shape.getPosition().x;
        this->destination.y = newHusband->shape.getPosition().y;
        this->currentState = eat;
        this->food = newHusband;
    } else {
        food = nullptr;
    }
}

void Grasseaters::findSex() {
    float localMin = 100000;
    Grasseaters *newHusband;
    bool check = false;
    for (auto &who: grasseaters) {
        float distance = sqrt((this->shape.getPosition().x - who->shape.getPosition().x) *
                              (this->shape.getPosition().x - who->shape.getPosition().x) +
                              (this->shape.getPosition().y - who->shape.getPosition().y) *
                              (this->shape.getPosition().y - who->shape.getPosition().y));
        if (distance < localMin && who->currentState == walk && this != who && who->needOfSex > sexGate) {
            check = true;
            localMin = distance;
            newHusband = who;
        }
    }
    if (check) {
        this->destination.x = (this->shape.getPosition().x + newHusband->shape.getPosition().x) / 2;
        this->destination.y = (this->shape.getPosition().y + newHusband->shape.getPosition().y) / 2;
        newHusband->destination = this->destination;

        this->currentState = sex;
        newHusband->currentState = sex;

        this->target = newHusband;
        newHusband->target = this;
    } else {
        target = nullptr;
    }
}

void Grasseaters::renderVector(sf::RenderTarget *target) {
    for (auto &eater: grasseaters) {
        eater->render(target);
    }
}

Grasseaters::~Grasseaters() {
    const int len = Grasseaters::grasseaters.size();
    int i;
    for (i = 0; i < len; i++) {
        if (Grasseaters::grasseaters[i] == this) {
            break;
        }
    }
    Grasseaters::grasseaters.erase(Grasseaters::grasseaters.begin() + i);
}

void Grasseaters::initGrasseates() {
    Grasseaters::texture.loadFromFile("textures/sheep.png");
    for (int i = 0; i < GRASSEATERS_START; i++)
        Grasseaters::grasseaters.push_back(new Grasseaters());
    for (auto obj: Grasseaters::grasseaters) {
        obj->setRandomDestination();
    }
}

std::vector<Grasseaters *> Grasseaters::grasseaters;
sf::Texture Grasseaters::texture;