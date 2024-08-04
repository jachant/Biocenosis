#include "Game.h"

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    this->window->setFramerateLimit(FPS);
}


void Game::initBackground() {
    backgroundTexture.loadFromFile("textures/background.png");
    background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setTexture(&backgroundTexture);
}


Game::Game() {
    this->initWindow();
    Grass::initGrass();
    Grasseaters::initGrasseates();
    Hunter::initHunters();
    this->initBackground();
    Rain::initRain();
    Particles::initParticles();
}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->sfEvent)) {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update() {
    timeCount++;
    this->updateSFMLEvents();
    const int huntersCount = Hunter::hunters.size();
    int grasseatersCount = Grasseaters::grasseaters.size();
    //std::cout << huntersCount << " " << grasseatersCount << '\n';
    if (grasseatersCount < 1) {
        std::cout << "Всех съели, время: " << timeCount << '\n';
        this->window->close();
        return;
    }
    if (huntersCount < 1) {
        std::cout << "Все сдохли, время: " << timeCount << '\n';
        this->window->close();
        return;
    }
    for (int i = 0; i < huntersCount; i++) {
        Hunter::hunters[i]->update();
        Hunter::hunters[i]->findWalk();
    }
    grasseatersCount = Grasseaters::grasseaters.size();
    for (int i = 0; i < grasseatersCount; i++) {
        Grasseaters::grasseaters[i]->update();
        Grasseaters::grasseaters[i]->findWalk();
    }
    if (Rain::rain[0]->checkState()) {
        grassCounter++;
        if (grassCounter % 10 == 0)
            Grass::grass.push_back(new Grass);
    }
}

void Game::render() {
    this->window->clear();
    this->window->draw(background);
    Rain::rain[0]->checkState();
    Grass::renderVector(this->window);
    Grasseaters::renderVector(this->window);
    Hunter::renderVector(this->window);
    Rain::renderVector(this->window);
    Particles::renderVector(this->window);
    this->window->display();
}

Game::~Game() {
    delete this->window;
}

void Game::run() {
    while (this->window->isOpen()) {
        Game::updatedt();
        this->update();
        this->render();
    }
}

void Game::updatedt() {
    dt = dtClock.restart().asSeconds() * 0.5;
}

sf::Clock Game::dtClock;
float Game::dt;