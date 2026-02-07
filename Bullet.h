#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Bullet {
private:
    sf::Sprite bulletSprite;
    sf::Vector2f direction;
    float movementSpeed;

public:
    // Constructor and destructor
    // texture: Bullet texture
    // pos: Initial position (player's center)
    // angle: Angle in degrees where it will travel
    // speed: Bullet speed
    Bullet(sf::Texture* texture, sf::Vector2f pos, float angle, float speed);
    virtual ~Bullet();

    // Accessor
    const sf::FloatRect getBounds() const;

    // Function
    void update();
    void render(sf::RenderTarget& target);
};