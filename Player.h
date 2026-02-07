#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>

class Player {
private:

    // Variables
    sf::Sprite sprite;
    sf::Texture texture;

    // Physics var
    float movementSpeed;
    float rotationSpeed;

    // Shot
    float attackCoolDown;
    float attackCoolDownMax;

    // Private functions
    void initVaribles();
    void initTexture();
    void initSprite();

public:
    Player();
    virtual ~Player();

    // Accessor
    const sf::Vector2f& getPos();
    const sf::FloatRect getBounds() const;
    float getRotation() const;

    // Functions
    const bool canAttack(); // Check and reset the cooldown
    void updateAttack(); // Increase the cooldown counter

    void updateInputs();
    void updateMovement(sf::Vector2f mousePos);
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget& target);

};
