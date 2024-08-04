//
// Created by Андрей Степанов on 28.03.2024.
//

#include "Alives.h"
#include <iostream>
#include "Game.h"

Alives::~Alives() {

}

Alives::Alives() : Entity() {
    this->shape.setSize(sf::Vector2f(SPRITE_SIZE, SPRITE_SIZE));
    currentState = walk;
}

Alives::Alives(const float x, const float y) : Entity(x, y) {
    this->shape.setSize(sf::Vector2f(SPRITE_SIZE, SPRITE_SIZE));
    currentState = walk;
}


void Alives::update() {
    this->hunger += 1;
    this->liveTime += 1;
    this->needOfSex += 1;
    if (liveTime > deathLimit || hunger > hungerLimit) {
        if (this->target != nullptr)
            this->target->target = nullptr;
        //Particles::particles.push_back(new Particles(this->shape.getPosition().x, this->shape.getPosition().y));
        delete this;
    } else if (hunger > hungerGate &&
               (this->currentState == walk || (this->currentState == eat && this->name == "hunter"))) {
        findFood();
    } else if (needOfSex > sexGate && this->currentState == walk) {
        findSex();
    }
    if (currentState == eat) {
        if (name == "hunter") {
            const int grasseatersCount = Grasseaters::grasseaters.size();
            bool isInArray = false;
            for (int i = 0; i < grasseatersCount; i++) {
                if (this->food == Grasseaters::grasseaters[i]) {
                    isInArray = true;
                    break;
                }
            }
            if (!isInArray) {
                findFood();
            }
        }
        if (name == "grasseater") {
            const int grassCount = Grass::grass.size();
            bool isInArray = false;
            for (int i = 0; i < grassCount; i++) {
                if (this->food == Grass::grass[i]) {
                    isInArray = true;
                    break;
                }
            }
            if (!isInArray) {
                this->food = nullptr;
                findFood();
            }
        }
    }
    if (currentState == sex) {
        if (name == "hunter") {
            const int partners = Hunter::hunters.size();
            bool isInArray = false;
            for (int i = 0; i < partners; i++) {
                if (this->target == Hunter::hunters[i]) {
                    isInArray = true;
                    break;
                }
            }
            if (!isInArray) {
                findSex();
            }
        }
        if (name == "grasseater") {
            const int partners = Grasseaters::grasseaters.size();
            bool isInArray = false;
            for (int i = 0; i < partners; i++) {
                if (this->target == Grasseaters::grasseaters[i]) {
                    isInArray = true;
                    break;
                }
            }
            if (!isInArray) {
                findSex();
            }
        }
    }
}

void Alives::findWalk() {
    if (this->destination.x > WINDOW_WIDTH - SPRITE_SIZE){
        this->destination.x = WINDOW_WIDTH - SPRITE_SIZE;
    }
    if (this->destination.y > WINDOW_WIDTH - SPRITE_SIZE){
        this->destination.y = WINDOW_WIDTH - SPRITE_SIZE;
    }
    sf::Vector2f direction = this->destination - this->shape.getPosition();

    float lenght = sqrt(direction.x * direction.x + direction.y * direction.y);

    sf::Vector2f normalized = direction / lenght * float(speed) * Game::dt;

    normalized.x -= normalized.x > 0 ? remainderf(normalized.x, 1.0) : -(remainderf(normalized.x, 1.0) + 1);
    normalized.y -= normalized.y > 0 ? remainderf(normalized.y, 1.0) : -(remainderf(normalized.y, 1.0) + 1);

    if (this->shape.getPosition().x + normalized.x > WINDOW_WIDTH - SPRITE_SIZE)
        normalized.x = WINDOW_WIDTH - this->shape.getPosition().x - SPRITE_SIZE;
    if (this->shape.getPosition().y + normalized.y > WINDOW_WIDTH - SPRITE_SIZE)
        normalized.y = WINDOW_WIDTH - this->shape.getPosition().y - SPRITE_SIZE;

    this->shape.move(normalized);
    checkDestination();
}


void Alives::setRandomDestination() {
    this->destination = sf::Vector2f(rand() % (WINDOW_WIDTH - SPRITE_SIZE), rand() % (WINDOW_HEIGHT - SPRITE_SIZE));
}

void Alives::changeStateAfterSex() {
    this->needOfSex = 0;
    this->currentState = walk;
}

void Alives::changeStateAfterEat() {
    this->hunger = 0;
    this->currentState = walk;
}

void Alives::checkDestination() {
    if (abs(this->shape.getPosition().x - this->destination.x) < 5 &&
        abs(this->shape.getPosition().y - this->destination.y) < 5) {
        if (this->currentState == sex) {
            if (this->target != nullptr) {
                this->changeStateAfterSex();
                this->target->changeStateAfterSex();
                if (this->name == "hunter") {
                    if (Hunter::hunters.size() < 30)
                    Hunter::hunters.push_back(new Hunter(this->shape.getPosition().x, this->shape.getPosition().y));
                }
                if (this->name == "grasseater") {
                    Grasseaters::grasseaters.push_back(
                            new Grasseaters(this->shape.getPosition().x, this->shape.getPosition().y));
                }
            }
        }
        if (this->currentState == eat) {
            this->changeStateAfterEat();
            const int partners = Grasseaters::grasseaters.size();
            bool isInArray = false;
            for (int i = 0; i < partners; i++) {
                if (this->target == Grasseaters::grasseaters[i]) {
                    isInArray = true;
                    break;
                }
            }
            if (!isInArray) {
                findSex();
            } else {
                delete this->food;
            }
        }
        setRandomDestination();
    }
}

