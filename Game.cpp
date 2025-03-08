#include "Game.hpp"
#include "BattleGround.hpp"
#include <iostream>

// 🔹 Define base resolution
sf::Vector2u Game::baseResolution = sf::Vector2u(1920, 1080);
float Game::scaleX = 1.0f;
float Game::scaleY = 1.0f;

Game::Game() : window(sf::VideoMode(1920, 1080), "Pirates vs Predators"), currentState(MENU) {
    battleground = new BattleGround(this);  // Initialize pointer
    
    // 🔹 Calculate scaling factors based on actual window size
    sf::Vector2u windowSize = window.getSize();
    scaleX = static_cast<float>(windowSize.x) / baseResolution.x;
    scaleY = static_cast<float>(windowSize.y) / baseResolution.y;

    std::cout << "[DEBUG] ScaleX: " << scaleX << ", ScaleY: " << scaleY << std::endl;
}

sf::RenderWindow& Game::getWindow() {
    return window;
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {

        float deltaTime = clock.restart().asSeconds();
        window.clear();

        switch (currentState) {
            case MENU:
                menu.handleInput(window, *this);
                menu.display(window);
                break;
            case INSTRUCTIONS:
                instructions.display(window);
                instructions.handleInput(window, *this);
                break;
            case HIGHSCORE:
                highScore.display(window);
                highScore.handleInput(window, *this);
                break;
            case BATTLE:
                battleground->handleInput(window);
                battleground->update(deltaTime);
                battleground->render(window);
                break;
            case GAME_OVER:
                gameOverScreen.display(window);
                gameOverScreen.handleInput(window, *this);
                break;
        }

        window.display();
    }
}

void Game::changeState(GameState newState) {
    currentState = newState;
}



void Game::restartGame(bool isMenu) {
    std::cout << "[DEBUG] Restarting the Game..." << std::endl;

    // **Delete and Recreate BattleGround**
    delete battleground;
    battleground = new BattleGround(this);

    // **Reset to Battle State**
    if (isMenu) changeState (MENU);
    else changeState(BATTLE);
}
