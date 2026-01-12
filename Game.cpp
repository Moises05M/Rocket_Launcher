
#include "Game.h"

// Window and private functions
void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Rocket launcher", sf::Style::Close || sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initPlayer() {
    this->player = new Player();
}

// constructor and destructor
Game::Game() {
    this->initWindow();
    this->initPlayer();
}

Game::~Game() {
    delete this->window;
    delete this->player;
}

// functions
void Game::run() {
    while (this->window->isOpen()) {
        this->update();
        this->render();
    }
}

void Game::updatePollEvents() {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) this->window->close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) this->window->close();
    }
}

void Game::update() {
    this->updatePollEvents();

    // Get mouse position relative to the window (mapped to world coordinates)
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*this->window);
    sf::Vector2f mousePos = this->window->mapPixelToCoords(pixelPos);

    // update player by sending mouse position
    this->player->update(mousePos);
}

void Game::render() {
    this->window->clear(sf::Color(20, 20, 30)); // Fondo oscuro

    this->player->render(*this->window);

    this->window->display();
}
