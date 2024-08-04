//
// Created by Лаба on 27.03.2024.
//

#include "Entity.h"

Entity::Entity() {
    this->shape.setPosition(rand() % (WINDOW_WIDTH - SPRITE_SIZE), rand() % (WINDOW_HEIGHT - SPRITE_SIZE));
}

Entity::Entity(const float x, const float y) {
    this->shape.setPosition(x, y);
}

void Entity::render(sf::RenderTarget *target) {
    target->draw(this->shape);
}
