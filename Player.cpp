
#include "Player.h"

// Private functions
void Player::initVaribles() {
    this->movementSpeed = 5.f;
    this->rotationSpeed = 4.f; // 4 degrees per frames
    this->attackCoolDownMax = 10.f;
    this->attackCoolDown = this->attackCoolDownMax;
}

void Player::initTexture() {
    if (!this->texture.loadFromFile("sprites/ship.png")) {
        std::cout << "ERROR::PLAYER::No se pudo cargar player.png" << std::endl;
    }
}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.3f, 0.3f); // Scale

    // axis at the origin
    this->sprite.setOrigin(
        this->sprite.getLocalBounds().width / 2.f,
        this->sprite.getLocalBounds().height / 2.f
    );

    // Initial position
    this->sprite.setPosition(400.f, 300.f);
}

// Constructor and destructor
Player::Player() {
    this->initVaribles();
    this->initTexture();
    this->initSprite();
}

Player::~Player() {
}

// Accessors
const sf::Vector2f & Player::getPos() {
    return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const {
    return this->sprite.getGlobalBounds();
}

float Player::getRotation() const {
    return this->sprite.getRotation();
}

// Functions
const bool Player::canAttack() {
    if (this->attackCoolDown >= this->attackCoolDownMax) {
        this->attackCoolDown = 0.f;
        return true;
    }
    return false;
}

void Player::updateAttack() {
    if (this->attackCoolDown < this->attackCoolDownMax) {
        this->attackCoolDown += 0.5f;
    }
}

void Player::updateInputs() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->sprite.rotate(-this->rotationSpeed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->sprite.rotate(this->rotationSpeed);
    }
}

void Player::updateMovement(sf::Vector2f mousePos) {
    // calculation of the vector towards the mouse
    sf::Vector2f playerPos = this->sprite.getPosition();
    sf::Vector2f mouseDir = mousePos - playerPos; // direction

    // distance of the vector (magnitude)
    float length = std::sqrt(mouseDir.x * mouseDir.x + mouseDir.y * mouseDir.y);

    // Nomalize and move only if we're far from the mouse
    if (length > 10.f) {
        sf::Vector2f normalizedDir = mouseDir / length;
        this->sprite.move(normalizedDir * this->movementSpeed);
    }
}

void Player::update(sf::Vector2f mousePos) {
    this->updateInputs();
    this->updateMovement(mousePos);
    this->updateAttack();
}

void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}
