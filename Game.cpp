
#include "Game.h"

// Window and private functions
void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Rocket launcher", sf::Style::Close || sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initVariables() {
    this->spawnTimerMax = 500.f;
    this->spawnTimer = this->spawnTimerMax;
}

void Game::initTextures() {
    this->textures["BULLET"] = new sf::Texture();
    if(!this->textures["BULLET"]->loadFromFile("sprites/bullet_02.png")){
        std::cout << "ERROR::GAME::No se cargo bullet_02.png" << std::endl;
    }

    this->textures["MISSILE"] = new sf::Texture();
    this->textures["MISSILE"]->loadFromFile("sprites/missile.png");
}

void Game::initPlayer() {
    this->player = new Player();
}

// constructor and destructor
Game::Game() {
    this->initWindow();
    this->initVariables();
    this->initTextures();
    this->initPlayer();
}

Game::~Game() {
    delete this->window;
    delete this->player;

    // clean textures player
    for (auto &i : this->textures) {
        delete i.second;
    }

    // clean bulltes
    for (auto *i : this->bullets) {
        delete i;
    }

    // clean missiles
    for (auto *i : this->missiles) {
        delete i;
    }
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

void Game::updateInput() {
    // shot
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()) {

        // get player data
        sf::Vector2f pPos = this->player->getPos();
        float pRot = this->player->getRotation();

        // calculate the position of the tip of the cannon
        // distance from the center of the ship to the tip of the cannon
        float offsetDist = 80.f;

        // convert degrees to radians (remembering the -90 of the sprite that faces up)
        float rad = (pRot - 90.f) * (3.14159265f / 180.f);

        // calculate displacement
        float offsetX = std::cos(rad) * offsetDist;
        float offsetY = std::sin(rad) * offsetDist;

        // final starting position
        sf::Vector2f spawnPos = sf::Vector2f(pPos.x + offsetX, pPos.y + offsetY);

        // create the bullet in the new position
        this->bullets.push_back(
            new Bullet(
                this->textures["BULLET"],
                spawnPos,    // use the new calculated position
                pRot,        // the same angle as the player
                10.f         // speed
            )
        );
    }
}

void Game::updateCollision() {
    // for each missile
    for (int i = 0; i < this->missiles.size(); ++i) {

        bool missileRemoved = false;

        // calcular vector de diferencia
        float dx = this->player->getPos().x - this->missiles[i]->getPos().x;
        float dy = this->player->getPos().y - this->missiles[i]->getPos().y;

        // calcular la distancia real (Hipotenusa)
        float distance = std::sqrt(dx * dx + dy * dy);

        // verificar si están tocándose
        // 50.f es el "Radio de colisión".
        // Si la suma de los radios de tu nave y el misil es menor a 50 pixeles, explota.
        // Juega con este número: Si se destruye muy lejos, bájalo a 30.f. Si atraviesa la nave, súbelo a 60.f.
        if (distance < 40.f) {

            std::cout << "Impacto directo!" << std::endl;

            delete this->missiles[i];
            this->missiles.erase(this->missiles.begin() + i);
            missileRemoved = true;
        }

        // if the missile has already been destroyed by hitting the player, we don't check bullets for that missile
        if (missileRemoved) {
            --i; // Adjust the index because we deleted an item
            continue;
        }

        // Collsion Bullet vs Missile
        for (size_t k = 0; k < this->bullets.size(); ++k) {

            if (this->missiles[i]->getBounds().intersects(this->bullets[k]->getBounds())) {

                this->missiles[i]->takeDamage(1); // damage

                // remove the bullet on impact
                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);
                --k; // adjust the index of bullet

                // if the missile runs out of life
                if (this->missiles[i]->getHp() <= 0) {
                    std::cout << "Misil eliminado por falta de HP" << std::endl;
                    delete this->missiles[i];
                    this->missiles.erase(this->missiles.begin() + i);
                    missileRemoved = true;
                    --i; // adjust the index missile
                    break; // exit the bullet loop because the missile no longer exists
                }
            }
        }
    }
}

void Game::updateBullets() {
    for (size_t i = 0; i < this->bullets.size(); i++) {
        this->bullets[i]->update();

        // Remove if it goes off-screen (Simple Culling)
        sf::FloatRect bounds = this->bullets[i]->getBounds();
        if (bounds.top < 0.f || bounds.top > 600.f ||
            bounds.left < 0.f || bounds.left > 800.f) {

            delete this->bullets[i];
            this->bullets.erase(this->bullets.begin() + i);
            i--; // decrement i to avoid skipping the next element after deleting
            }
    }
}

void Game::updateMissiles() {
    // spawning missiles
    this->spawnTimer += 1.f;
    if (this->spawnTimer >= this->spawnTimerMax) {
        // create missile in random position
        float x = static_cast<float>(rand() % 800);
        float y = static_cast<float>(rand() % 600);

        // Evitar que aparezca encima del jugador (simple check)
        // Por ahora lo dejamos aleatorio para probar
        this->missiles.push_back(new Missile(this->textures["MISSILE"], x, y));

        this->spawnTimer = 0.f;
    }

    // update and cleaning
    for (size_t i = 0; i < this->missiles.size(); ++i) {
        // update movement chasing the player
        this->missiles[i]->update(this->player->getPos());
    }
}

void Game::update() {
    this->updatePollEvents();

    // Get mouse position relative to the window (mapped to world coordinates)
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*this->window);
    sf::Vector2f mousePos = this->window->mapPixelToCoords(pixelPos);

    // update player by sending mouse position
    this->player->update(mousePos);

    this->updateInput(); // check shot
    this->updateBullets(); // move bullets
    this->updateMissiles();
    this->updateCollision();
}

void Game::render() {
    this->window->clear(sf::Color(20, 20, 30)); // Fondo oscuro

    this->player->render(*this->window);

    // draw bullets
    for (auto *bullet : this->bullets) {
        bullet->render(*this->window);
    }

    // render missiles
    for (auto *missile : this->missiles) {
        missile->render(*this->window);
    }

    this->window->display();
}
