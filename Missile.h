#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Missile {
private:
    sf::Sprite missileSprite;

    // physics
    sf::Vector2f direction;
    float movementSpeed;
    float rotateSpeed;

    // lives
    int hp;
    int hpMax;

    // private function
    void initVariables();

public:
    // Constructor and destructor
    Missile(sf::Texture* texture, float posX, float posY);
    virtual ~Missile();

    // Accessors
    const sf::FloatRect getBounds() const;
    const sf::Vector2f& getPos();
    const int getHp() const;

    // Funciones
    void takeDamage(int damage);
    void updateMovement(const sf::Vector2f& playerPos);
    void update(const sf::Vector2f& playerPos);
    void render(sf::RenderTarget& target);
};