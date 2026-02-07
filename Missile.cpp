
#include "Missile.h"

// private functions
void Missile::initVariables() {
    this->movementSpeed = 2.5f;
    this->rotateSpeed = 2.0f;
    this->hpMax = 3;
    this->hp = this->hpMax;
}

// Constructor and destructor
Missile::Missile(sf::Texture *texture, float posX, float posY) {
    this->initVariables();

    this->missileSprite.setTexture(*texture);
    this->missileSprite.setPosition(posX, posY);

    // scale and origin (center)
    this->missileSprite.scale(0.3f, 0.3f);
    this->missileSprite.setOrigin(
        this->missileSprite.getGlobalBounds().width / 2.f,
        this->missileSprite.getGlobalBounds().height / 2.f
    );
}

Missile::~Missile() {
}

// Accessor
const sf::FloatRect Missile::getBounds() const {
    return this->missileSprite.getGlobalBounds();
}

const sf::Vector2f & Missile::getPos() {
    return this->missileSprite.getPosition();
}

const int Missile::getHp() const {
    return this->hp;
}

// Functions
void Missile::takeDamage(int damage) {
    this->hp -= damage;
    if (this->hp < 0) this->hp = 0;
}

void Missile::updateMovement(const sf::Vector2f &playerPos) {
    // calculate the difference between the player and the missile
    float dtX = playerPos.x - this->missileSprite.getPosition().x;
    float dtY = playerPos.y - this->missileSprite.getPosition().y;

    // calculate the desired angle in Degrees (atan2 returns radians)
    const float PI = 3.14159265f;
    float deg = std::atan2(dtY, dtX) * 180.f / PI;

    // since the sprite is facing UP, we add 90 degrees
    // so that the missile's "front" matches the mathematical angle.
    float targetRotation = deg + 90.f;

    // Smooth rotation
    float currentRotation = this->missileSprite.getRotation();

    // calculate the difference between angles
    float diff = targetRotation - currentRotation;

    // normalize the difference to take the shortest path (-180 to 180)
    while (diff < -180.f) diff += 360.f;
    while (diff > 180.f) diff -= 360.f;

    // apply limited rotation by rotateSpeed
    if (diff > this->rotateSpeed)
        this->missileSprite.rotate(this->rotateSpeed);
    else if (diff < -this->rotateSpeed)
        this->missileSprite.rotate(-this->rotateSpeed);
    else
        this->missileSprite.setRotation(targetRotation); // If it's too close, set exact

    // move forward in the direction the missile is now facing
    // subtract 90 to convert from 'Sprite Degrees' to 'Mathematical Radians'
    float rad = (this->missileSprite.getRotation() - 90.f) * (PI / 180.f);

    this->missileSprite.move(std::cos(rad) * this->movementSpeed, std::sin(rad) * this->movementSpeed);
}

void Missile::update(const sf::Vector2f &playerPos) {
    this->updateMovement(playerPos);
}

void Missile::render(sf::RenderTarget &target) {
    target.draw(this->missileSprite);
}


