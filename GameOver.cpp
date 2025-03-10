#include "GameOver.hpp"
#include <iostream>

GameOver::GameOver(Game *game) : game(game) {
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
    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setPosition(750, 300);

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(72);
    finalScoreText.setFillColor(sf::Color::Red);
    finalScoreText.setPosition(750, 400);

    playerNameText.setFont(font);
    playerNameText.setCharacterSize(72);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setPosition(750, 450);

}

void GameOver::display(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(gameOverText);
    window.draw(finalScoreText);  // ✅ Draw final score    
    window.draw(menuButton);
    window.draw(playerNameText);
    window.display ();
}

void GameOver::handleInput(sf::RenderWindow &window) {
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
                game->saveScore();  // ✅ Save score before exiting
                game->restartGame (true);
            }
        }
    }
}

void GameOver::updateFinalScore(int score, const std::string& name) {
    finalScoreText.setString("Final Score: " + std::to_string(score));
    playerNameText.setString("Player: " + name);
}
