#include "GameOver.hpp"
#include "Game.hpp"
#include <iostream>

GameOver::GameOver() {
    if (!backgroundTexture.loadFromFile("assets/gameover_screen.png")) {
        std::cerr << "[ERROR] Failed to load game over background!" << std::endl;
    }
    background.setTexture(backgroundTexture);
    background.setScale(1.0f, 1.0f);

    if (!menuButtonTexture.loadFromFile("assets/quit_button_small.png")) {
        std::cerr << "[ERROR] Failed to load menu button!" << std::endl;
    }
    menuButton.setTexture(menuButtonTexture);
    menuButton.setPosition(800, 500);
    menuButton.setScale(1.0f, 1.0f);

    if (!font.loadFromFile("assets/custom_font.ttf")) {
        std::cerr << "[ERROR] Failed to load font!" << std::endl;
    }
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(72);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(750, 300);
}

void GameOver::display(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(gameOverText);
    window.draw(menuButton);
    window.display ();
}

void GameOver::handleInput(sf::RenderWindow &window, Game &game) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            if (menuButton.getGlobalBounds().contains(worldPos)) {
                std::cout << "[DEBUG] Menu Button Clicked! Returning to Menu." << std::endl;
                game.restartGame (true);
            }
        }
    }
}
