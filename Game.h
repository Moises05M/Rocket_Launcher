#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game {
private:
    // Window
    sf::RenderWindow* window;

    // Resouces

    // Player
    Player* player;

    // Private functions
    void initWindow();
    void initPlayer();

public:
    // Constructor and destructor
    Game();
    virtual ~Game();

    // Function
    void run(); // loop
    void updatePollEvents(); // updates
    void update();
    void render(); // draw
};
