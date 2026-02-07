
#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, sf::Vector2f pos, float angle, float speed) {
    this->bulletSprite.setTexture(*texture);
    this->bulletSprite.setPosition(pos);
    this->bulletSprite.setRotation(angle); // same angle of the player

    this->bulletSprite.scale(0.3f, 0.3f);
    this->bulletSprite.setOrigin(
        (this->bulletSprite.getGlobalBounds().width / 2.f) + 90.f, // 90 SO THAT IT COMES OUT IN THE MIDDLE OF THE SHIP
        this->bulletSprite.getGlobalBounds().height / 2.f
    );

    this->movementSpeed = speed;

    // since "0 degrees" is UP, but the "mathematical 0" is RIGHT,
    // it's offset by 90 degrees. Subtract 90.
    float rad = (angle - 90.f) * (3.14159265f / 180.f);

    this->direction.x = std::cos(rad);
    this->direction.y = std::sin(rad);
}

Bullet::~Bullet() {
}


// Accessor
const sf::FloatRect Bullet::getBounds() const {
    return this->bulletSprite.getGlobalBounds();
}

// Functions
void Bullet::update() {
    // Move in the calculated direction
    this->bulletSprite.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget &target) {
    target.draw(this->bulletSprite);
}
