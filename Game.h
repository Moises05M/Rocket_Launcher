#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Missile.h"

class Game {
private:
    // Window
    sf::RenderWindow* window;

    // Resouces
    std::map<std::string, sf::Texture*> textures;

    // Player
    Player* player;
    std::vector<Bullet*> bullets; // Bullet list

    // Enemy
    std::vector<Missile*> missiles;
    float spawnTimer;
    float spawnTimerMax;

    // Private functions
    void initWindow();
    void initVariables();
    void initTextures();
    void initPlayer();

public:
    // Constructor and destructor
    Game();
    virtual ~Game();

    // Function
    void run(); // loop
    void updatePollEvents(); // updates
    void updateInput(); // to shoot
    void updateCollision();
    void updateBullets(); // move and delete bullets
    void updateMissiles();
    void update();
    void render(); // draw
};
